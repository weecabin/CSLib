#ifndef DATATOOLS_H
#define DATATOOLS_H

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
    sum+=x;
    if (x<min)
      min=x;
    if (x>max)
      max=x;
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
};

#endif