#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <sys/time.h>
#include "CircularBuffer.h"
#include <string>
#include <cmath>

class MyTime
{
  public:
  MyTime()
  {
    gettimeofday(&begin,0);
  }
  unsigned long millis()
  {
    timeval temp;
    gettimeofday(&temp,0);
    unsigned long seconds = (temp.tv_sec-begin.tv_sec);
    unsigned long ms = (temp.tv_usec-begin.tv_usec)/1000;
    if (ms<0)
    {
      seconds-=1;
      ms +=1000;
    }
    ms += seconds*1000;
    return ms;
  }
  private:
  timeval begin;
};

MyTime mytime;

class MeasureTime
{
  public:
  void Start()
  {
    startTime=mytime.millis();
  }
  void Stop()
  {
    stopTime=mytime.millis(); 
  }
  float Result()
  {
    return  stopTime-startTime;
  }
  private:
  unsigned long  startTime;
  unsigned long  stopTime;
};

enum RunStatus {waiting,runcomplete,killme};

class BaseTask
{
  public:
  // functionPtr = pointer to function called when task runs
  // runIntervalSeconds = time between task starts
  // starts = number of times to run. kill task after this
  BaseTask(float runIntervalSeconds, int starts=0)
  {
    runInterval = runIntervalSeconds*1000;
    this->starts = starts;
  }
  virtual ~BaseTask()
  {

  }
  bool TimeToRun(unsigned long currentTime) 
  {
    return currentTime >= nextRunTime;
  }
  void SetRunTime(unsigned long current)
  {
    if (!running)
    {
      //std::cout<<"not running\n";
      nextRunTime=current+runInterval;
    }
    else
    {
      //std::cout<<"running\n";
      nextRunTime+=runInterval;
    }
    //std::cout<<"next run time: "<<nextRunTime<<"\n";
  }

  // Runs only if it's time to run
  RunStatus Run(unsigned long currentTime)
  {
    if(!TimeToRun(currentTime))
      return waiting;
    running=true;
    Run();
    if (starts!=0)
    {
      if (--starts==0)
      return killme;
    }
    //std::cout<<"SetRunTime\n";
    SetRunTime(currentTime);
    return runcomplete;
  }
  // always runs. its up to the calling task to determine if its time
  virtual void Run() = 0;

  private:
  unsigned long runInterval;
  unsigned long nextRunTime;
  unsigned int starts;
  bool running=false;
};

class FunctionTask : public BaseTask
{
  public:
  FunctionTask(void (*functionPtr)(),float runIntervalSeconds, int starts=0):
      BaseTask(runIntervalSeconds,starts)
{
  taskPtr=functionPtr;
}
~FunctionTask()
{
  std::cout<<"In ~FunctionTask\n";
}
void Run()
{
  taskPtr();
}
private:
void (*taskPtr)();
};

class ExampleTask : public BaseTask
{
  public:
  ExampleTask(const char* name,float runIntervalSeconds, int starts=0):
      BaseTask(runIntervalSeconds,starts)
  {
    this->name = name;
  }
  ~ExampleTask()
  {
    std::cout<<"In ~ExampleTask";
  }
  void Run()
  {
    std::cout<<name<<"("<<++count<<")\n";
  }
  private:
  const char* name;
  int count=0;
};

/*
Used to run tasks at a defined rate.
*/
class Scheduler
{
  public:
  Scheduler(int maxTasks)
  {
    buff.SetSize(maxTasks);
  }

  void IdleTask(void (*idle)())
  {
    idleTask=idle;
  }
  void AddTask(BaseTask *task)
  {
    buff.Push(task);
  }
  ~Scheduler()
  {
    std::cout<<"In ~Scheduler\n";
    for(int i=0;i<buff.ValuesIn();i++)
      delete buff[i];
  }
  void Run(int seconds)
  { 
    MeasureTime m;
    // setup the outer loop
    unsigned long time = mytime.millis();
    unsigned long quitTime = seconds*1000 + time;
    
    // set the next runtime for every task
    for(int i=0;i<buff.ValuesIn();i++)
      buff[i]->SetRunTime(time);
    m.Start();
    do
    {
      if (idleTask!=NULL)
        idleTask();
      time = mytime.millis();
      for(int i=buff.ValuesIn()-1;i>=0;i--)
        HandleRunStatus(i,buff[i]->Run(time));
    }while(quitTime>time);
    m.Stop();
    std::cout << "\n";
    std::cout << m.Result();
    std::cout << "\n";
    std::cout << "End of Scheduler\n";
  }

  private:
  void HandleRunStatus(int taskIndex,RunStatus status)
  {
    switch (status)
    {
      case waiting:
      break;

      case runcomplete:
      break;

      case killme:
      std::cout<<"kill("<<taskIndex+1<<")\n";
      delete buff[taskIndex]; // free the memory of this object
      buff.Delete(taskIndex); // rearranges the array to fill this hole 
      break;
    }
  }
  void (*idleTask)()=NULL;
  CircularBuffer<BaseTask *> buff;
};
#endif