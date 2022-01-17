#ifndef DATATOOLS_H
#define DATATOOLS_H
#include "LinkedList.h"

class MinMaxDelta
{
  public:
  MinMaxDelta()
  {

  }
  void Add(float x)
  {
    if (valuesIn++==0)
    {
      min=x;
      max=x;
      sum=x;
      return;
    }
    ll.Add(x);
    sum+=x;
    if (x<min)
      min=x;
    if (x>max)
      max=x;
  }
  float Variance()
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
  float Stdev()
  {
    return pow(Variance(),.5);
  }
  float Min()
  {
    return min;
  }
  float Max()
  {
    return max;
  }
  float Sum()
  {
    return sum;
  }
  float Delta()
  {
    return max-min;
  }
  float Mean()
  {
    return sum/valuesIn;
  }
private:
  float min;
  float max;
  int valuesIn=0;
  float sum;
  LinkedList<float> ll;
};

#endif