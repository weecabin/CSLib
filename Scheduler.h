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

class SchedulerTask
{
  public:
  SchedulerTask(void (*functionPtr)(),float runIntervalSeconds, float runTimeSeconds=0)
  {
    taskPtr=functionPtr;
    runInterval = runIntervalSeconds*1000;
    endRunTime = runTimeSeconds*1000;
  }
  bool TimeToRun(unsigned long currentTime)
  {
    return currentTime >= nextRunTime;
  }
  void SetRunTime(unsigned long current)
  {
    if (!running)
    {
      nextRunTime=current+runInterval;
      endRunTime+=current;
    }
    else
      nextRunTime+=runInterval;
  }

  // Runs only if it's time to run
  RunStatus Run(unsigned long currentTime)
  {
    if(!TimeToRun(currentTime))
      return waiting;
    running=true;
    Run();
    if (endRunTime!=0 && currentTime>=endRunTime)
    {
      return killme;
    }
    SetRunTime(currentTime);
    return runcomplete;
  }
  // always runs. its up to the calling task to determine if its time
  void Run()
  {
    std::cout<<mytime.millis();
    taskPtr();
  }

  private:
  void (*taskPtr)();
  unsigned long runInterval;
  unsigned long nextRunTime;
  unsigned long endRunTime;
  bool running=false;
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
  void AddTask(SchedulerTask *task)
  {
    buff.Push(task);
  }
  ~Scheduler()
  {
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
      delete buff[taskIndex];
      buff.Delete(taskIndex); // rearranges the array to fill this hole 
      break;
    }
  }
  void (*idleTask)()=NULL;
  CircularBuffer<SchedulerTask *> buff;
};
#endif