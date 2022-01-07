#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <sys/time.h>
#include "CircularBuffer.h"
#include <string>
#include <cmath>

class MeasureTime
{
  public:
  void Start()
  {
    gettimeofday(&startTime,0);
  }
  void Stop()
  {
    gettimeofday(&stopTime,0); 
  }
  float Result()
  {
    float secs = stopTime.tv_sec - startTime.tv_sec;
    float usecs = stopTime.tv_usec - startTime.tv_usec;
    if (usecs<0)
    {
      secs--;
      usecs*=-1;
    }
    float ret = secs+usecs*.000001;
    return  ret;
  }
  private:
  timeval startTime;
  timeval stopTime;
};

class SchedulerTask
{
  public:
  SchedulerTask(void (*functionPtr)(),float runIntervalSeconds)
  {
    taskPtr=functionPtr;
    float secs = floor(runIntervalSeconds);
    float frac = runIntervalSeconds - (int)runIntervalSeconds;
    runInterval.tv_sec=secs;
    runInterval.tv_usec=1e6*frac;
  }
  bool TimeToRun(timeval currentTime)
  {
    return nextRunTime.tv_sec<=currentTime.tv_sec && nextRunTime.tv_usec<=currentTime.tv_usec;
  }
  void SetRunTime(timeval current)
  {
    nextRunTime=Add(current,runInterval);
  }
  timeval Add(timeval t1,timeval t2)
  {
    timeval ret;
    ret.tv_sec=t1.tv_sec+t2.tv_sec;
    ret.tv_usec=t1.tv_usec+t2.tv_usec;
    if (ret.tv_usec>=1000000)
    {
      ret.tv_sec+=1;
      ret.tv_usec-=1000000;
    }
    return ret;
  }
  // Runs only if it's time to run
  bool Run(timeval currentTime)
  {
    if(!TimeToRun(currentTime))
      return false;
    Run();
    SetRunTime(currentTime);
    return true;
  }
  // always runs. its up to the calling task to determine if its time
  void Run()
  {
    taskPtr();
  }

  private:
  void (*taskPtr)();
  timeval runInterval;
  timeval nextRunTime;
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
    struct timeval time;
    struct timeval end;
    gettimeofday(&time, 0);
    end.tv_sec=time.tv_sec+seconds;
    end.tv_usec=time.tv_usec;

    // set the next runtime for every task
    for(int i=0;i<buff.ValuesIn();i++)
      buff[i]->SetRunTime(time);
    m.Start();
    do
    {
      if (idleTask!=NULL)
        idleTask();
      gettimeofday(&time,0);
      for(int i=0;i<buff.ValuesIn();i++)
        buff[i]->Run(time);
    }while(!TimeUp(end,time));
    m.Stop();
    std::cout << "\n";
    std::cout << m.Result();
    std::cout << "\n";
  }

  private:
  bool TimeUp(timeval target,timeval current)
  {
    return target.tv_sec<=current.tv_sec && target.tv_usec<=current.tv_usec;
  }
  void (*idleTask)()=NULL;
  CircularBuffer<SchedulerTask *> buff;
};
#endif