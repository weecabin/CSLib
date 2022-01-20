// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)

#include "CircularBuffer.h"
#include "CommandParser.h"
#include "Scheduler.h"
#include "MyStrings.h"
#include "PIDCtrl.h"
#include "Stats.h"
#include "LinkedList.h"
#include "Navigation.h"
#include "Map.h"
#include "MyDefines.h"
#include <vector>
#include <cstdlib>

void CircularBufferTest();
void CommandParserTest();
void SchedulerTest();
void PidCtrlTest();
void DataToolsTest();
void LinkedListTest();
void NavigationTest();
void MapTest();

int main() 
{
  MapTest();
  //NavigationTest();
  //LinkedListTest();
  //DataToolsTest();
  //PidCtrlTest();
  //SchedulerTest();
  //CommandParserTest();
  //CircularBufferTest();
  return 0;
}

const char key1[] = "k1";
const char key2[] = "k2";
const char key3[] = "k3";
const char key4[] = "k4";
const char key5[] = "k5";
void ListCallback(const char* key,float value)
{
  print("key:");print(key);print("=");println(value);
}
void MapTest()
{
  println("\n******** MapTest ********");
  println("Add (key1,100),(key2,200),(key3,300)");
  Map<const char*,float> m;
  m.Add(key1,100);
  println("Get a key value with only one in the map");
  print("key1: ");println(m.Value(key1));
  println("Add two more, then get them all");
  m.Add(key2,200);
  m.Add(key3,300);
  print("key1/key2: ");println(m.Value(key1)/m.Value(key2));
  println("m.Print()");
  m.Print();
  println("clear the map, then add 5 with AddSorted in the following order...");
  println("key5,key4,key3,key2,key1");
  m.Clear();
  println("m.Clear() completed");
  m.AddSorted(key5,500);
  m.AddSorted(key4,400);
  m.AddSorted(key3,300);
  m.AddSorted(key2,200);
  m.AddSorted(key1,100);
  println("m.Print()");
  m.Print();
  println("m.List");
  m.List(ListCallback);

  println("clear the map, then add 5 with AddSorted in the following order...");
  println("key1,key4,key3,key2,key5");
  m.Clear();
  println("m.Clear() completed");
  m.AddSorted(key1,100);
  m.AddSorted(key4,400);
  m.AddSorted(key3,300);
  m.AddSorted(key2,200);
  m.AddSorted(key5,500);
  println("m.Print()");
  m.Print();
  println("m.List");
  m.List(ListCallback);
  
  Map<float,vector<float>> mf;
  vector<float> v{1.1,2.2,3.3};
  mf.Add(.1,v);
  println(mf[.1][0]);
}

void NavigationTest()
{
  println("\n******** NavigationTest ********");
  
  print("HeadingError(5.1,355.2) (target,current) = ");
  println(HeadingError(5.1,355.2));

  print("HeadingError(730,710) = ");
  println(HeadingError(730,710));

  print("HeadingError(710,730) = ");
  println(HeadingError(710,730));

  print("HeadingError(710,710) = ");
  println(HeadingError(710,710));

  print("FixHeading(0) = ");
  println(FixHeading(0));
  
  print("FixHeading(370) = ");
  println(FixHeading(370));
  
  print("FixHeading(-10) = ");
  println(FixHeading(-10));
  
  print("FixHeading(180) = ");
  println(FixHeading(180));

  print("FixHeading(730) = ");
  println(FixHeading(730));

  print("FixHeading(710) = ");
  println(FixHeading(710));
}

void LinkedListTest()
{
  println("******** LinkedListTest ********");
  LinkedList<float> ll;
  ll.Add(1.1);
  
  // make sure list works with only one value in
  println("GetNext(true)...");
  println(ll.GetNext(true));
  while(!ll.EndNext())
    println(ll.GetNext());
  
  println("GetPrev(true)...");
  println(ll.GetPrev(true));
  while(!ll.EndPrev())
    println(ll.GetPrev());

  println("Add two more terms");
  ll.Add(2.2);
  ll.Add(3.3);

  println("Traverse up...");
  // This resets the iterator, and returns the first value
  println(ll.GetNext(true));
  while(!ll.EndNext())
    println(ll.GetNext());
  
  println("Traverse down...");
  // This resets the iterator, and returns the last value
  println(ll.GetPrev(true));
  while(!ll.EndPrev())
    println(ll.GetPrev());

  for (float f=4.0;f<10;f+=.5)
    ll.Add(f);
  
  println("LinkedList.Print()");
  ll.Print();
  
  println("Iterator... up...");
  for(auto itr = ll.Head(); itr != ll.End(); ++itr)
    std::cout << *itr << std::endl;

  println("Remove a node");
  auto itr = ll.Head();
  ++itr;
  itr.remove();
  println("Insert 99");
  itr.insert(99);
  println("find it");
  itr = ll.FindNext(99);
  if (itr!=ll.End())
  {
    print("found ");println(*itr);
  }

  println("Iterator... down...");
  for(auto itr = ll.Tail(); itr != ll.End(); --itr)
    std::cout << *itr << std::endl;

  println("From Head, *itr.next()...");
  itr = ll.Head();
  println(*itr.next());
  println("*itr.next(3)...");
  println(*itr.next(3));
  println("*itr.next(99), 0 indicates end...");
  println(*itr.next(99));
  println("*itr.prev()...");
  println(*itr.prev());
  println("*itr.findprev(6)...");
  println(*itr.findprev(6));
  println("*itr.findnext(9)...");
  println(*itr.findnext(9));

  println("list it before destructor executes");
  ll.Print();
}

void DataToolsTest()
{
  println("******** StatsTest ********");
  Stats stats;
  for (float f=1;f<10;f+=1)
  {
    stats.Add(f);      
  }
  stats.Print();
  /*
  print("Min: ");println(stats.Min());
  print("Max: ");println(stats.Max());
  print("Delta: ");println(stats.Delta());
  print("Sum: ");println(stats.Sum());
  print("Mean: ");println(stats.Mean());
  print("Variance: ");println(stats.Variance());
  print("stdev: ");println(stats.Stdev());
  */
}

// PID testing
void PidCtrlTest()
{
  PIDCtrl pid(1,1,0,1,10);
  println("Set target to 5");
  pid.Target(5);
  srand(2);
  float r = float(rand()%1000)/1000.0;
  for (int i=0;i<10;i++)
  {
    r = float(rand()%1000)/1000.0;
    pid.Add(4.5+r);
  }
  pid.Print();
  print("Correction: ");println(pid.Correction());
  print("delta: ");println(pid.DeltaError());
}

// Scheduler TEsting
int count1=0;
void task1()
{
  cout<<"Task1: "<<++count1<<"\n";
}

int count2=0;
void task2()
{
  cout<<"\tTask2: "<<++count2<<"\n";
}

int count3=0;
void task3()
{
  cout<<"\t\tTask3: "<<++count3<<"\n";
}
int count4=0;
void task4()
{
  cout<<"\t\t\tTask4: "<<++count4<<"\n";
}
int idle=0;
void idleTask()
{
  print("idleTask: ");println(++idle);
  MyTime t;
  // don't want to fill the screen with idleTask
  do{}while(t.millis()<20);
}
void SchedulerTest()
{
  std::cout<<"\n******** SchedulerTest ********\n";
  count1=count2=count3=count4=0;
  Scheduler s(5);
  // using FunctionTask as the idle task for convenience here
  // the runtime parameter won't be used, but it's needed
  s.IdleTask(new FunctionTask(idleTask,1));
  s.AddTask(new FunctionTask(task1,.1));
  s.AddTask(new FunctionTask(task2,.2));
  s.AddTask(new FunctionTask(task3,.3));
  s.AddTask(new FunctionTask(task4,.4));
  s.Run(5);
}

// CommandParser testing...
void GetHeading(char *paramstr)
{
  std::cout << "In GetHeading\n";
}

void SetHeading(char *paramstr)
{
  float floats[1]={0};
  ToFloat(paramstr,floats);
  
  int ints[1];
  ToInt(paramstr,ints);
  std::cout << "In SetHeading("<<floats[0]<<")\n";
  std::cout << "int param: "<<ints[0]<<"\n";
}
void SetPid(char *paramstr)
{
  float floats[3]={0,0,0};
  ToFloat(paramstr,floats);
  std::cout << "In SetPid("<<floats[0]<<","<<floats[1]<<","<<floats[2]<<")\n";
}

void CommandParserTest()
{
  std::cout<<"\n***** CommandParser Testing *****\n";
  CommandParser p;
  p.Add(GetHeading,GETHEADING);
  p.Add(SetHeading,SETHEADING);
  p.Add(SetPid,SETPID);
  char cmd1[] = "GetHeading()";
  p.Execute(cmd1);
  char cmd2[] = "SetHeading(60.1)";
  p.Execute(cmd2);
  char cmd3[]= "SetPid(1.1,2.2,3.3)";
  p.Execute(cmd3);
  char cmd4[]= "SetPid(1.1,2.2)";
  p.Execute(cmd4);
  char cmd5[]= "SetPid(1.1,2.2,5)";
  p.Execute(cmd5);
}

void CircularBufferTest()
{
  std::cout << "\n***** CircularBuffer Testing *****\n";
  std::cout << "Created buffer of 10 floats, then added more than 10\n";
  CircularBuffer<float> cb(10);
  //cb.SetSize(10);
  for (float i=1.1;i<20;i+=1.1)
    cb.Push(i);
  cb.Print();
  std::cout <<"delete the third entry\n";
  cb.Delete(2);
  cb.Print();
}

void SomeTestCode()
{
  
}