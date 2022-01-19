#include "Stats.h"
#include <cmath>
#include <iostream>

#ifndef PRINTX
#define PRINTX
#define print(x)(std::cout<<x)
#define println(x)(std::cout<<x<<"\n")
#endif

  Stats::Stats()
  {

  }
  void Stats::Add(float x)
  {
    if (valuesIn++==0)
    {
      min=x;
      max=x;
      sum=x;
      ll.Add(x);
      return;
    }
    ll.Add(x);
    sum+=x;
    if (x<min)
      min=x;
    if (x>max)
      max=x;
  }
  float Stats::Variance()
  {
    float mean=Mean();
    float var=0;
    for(auto itr=ll.Head();itr!=ll.End();++itr)
    {
      var += pow((*itr-mean),2);
    }
    var /=valuesIn;
    return var;
  }
  float Stats::Stdev()
  {
    return pow(Variance(),.5);
  }
  float Stats::Min()
  {
    return min;
  }
  float Stats::Max()
  {
    return max;
  }
  float Stats::Sum()
  {
    return sum;
  }
  float Stats::Delta()
  {
    return max-min;
  }
  float Stats::Mean()
  {
    return sum/valuesIn;
  }
  void Stats::Print()
  {
    print("Min: ");println(Min());
    print("Max: ");println(Max());
    print("Delta: ");println(Delta());
    print("Sum: ");println(Sum());
    print("Mean: ");println(Mean());
    print("Variance: ");println(Variance());
    print("stdev: ");println(Stdev());
  }
