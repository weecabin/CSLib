#ifndef STATS_H
#define STATS_H
#include "LinkedList.h"

class Stats
{
  public:
  Stats();
  void Add(float x);
  float Variance();
  float Stdev();
  float Min();
  float Max();
  float Sum();
  float Delta();
  float Mean();
  void Print();

  private:
  float min;
  float max;
  int valuesIn=0;
  float sum;
  LinkedList<float> ll;
};

#endif