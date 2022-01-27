#ifndef CIRCULARBUFFER2_H
#define CIRCULARBUFFER2_H

#include "MyDefines.h"

/*
CircularBuffer
Implements a buffer with a maximum size of size elements.
from the outside, new elements appear to be added at the beginning of
the buffer, and older elements are pushed down. if the newest element 
exceeds the buffer size, the oldest will be removed.
the array operator [0] returns the most recent addition, or the Head of the buffer.
*/

template <class T> class CircularBuffer2
{
  public:
  CircularBuffer2()
  {
    SetSize(1);
  }
  CircularBuffer2(int size)
  {
    SetSize(size);
  }
  ~CircularBuffer2()
  {
    //std::cout<<"in ~CircularBuffer\n";
    if (buffer!=0)
      delete [] buffer;
  }
  void SetSize(int size)
  {
    if(buffer!=nullptr)delete []buffer;
    buffer=new T[size];
    this->size=size;
    Clear();
  }
  void Clear()
  {
    valuesIn=0;
    current=end=-1;
  }
  void Print()
  {
    if (valuesIn==0)
    {
      std::cout << "Empty\n";
      return;
    }
    for (int i=0;i<valuesIn;i++)
      { 
        std::cout << i;
        std::cout << ": ";
        std::cout << (*this)[i];
        std::cout << "\n";
      }
  }
  bool Empty()
  {
    return valuesIn==0;
  }
  bool Full()
  {
    return valuesIn>=size;
  }
  void Push(T value)
  {
    if (++valuesIn>size)
      valuesIn=size;
    if (++current>=size)
    {
      current=0;
      end=size-1;
    }
    if (current==end)end--;
    if (end<0)end=size-1;
    buffer[current]=value;
  }
  T Head()
  {
    return (*this)[0];
  }
  T Tail()
  {
    return (*this)[valuesIn-1];
  }
  int ValuesIn()
  {
    return valuesIn;
  }
  void Insert(int d,T value)
  {
    if (d==0)
    {
      Push(value);
      return;
    }
    if (d>=valuesIn)return; // can't insert past the end
    for (int i=valuesIn==size?valuesIn-2:valuesIn-1;i>=d;i--)
    {
      buffer[Index(i+1)]=buffer[Index(i)];
    }
    buffer[Index(d)]=value;
    if (valuesIn==size)return;
    valuesIn++;
  }
  void Delete(int d)
  {
    for (int i=d;i<valuesIn-1;i++)
    {
      buffer[Index(i)]=buffer[Index(i+1)];
    }
    valuesIn--;
    return;
  }
  T operator[](int i)
  {
    if (i>=size || valuesIn==0)
      return *invalid;
    return buffer[Index(i)];
  }
  private:
  int Index(int i)
  {
    int temp=current-i;
    if (temp>=0)
      return temp;
    temp+=size;
    return temp;
  }
  T *buffer=nullptr;
  T *invalid=nullptr; 
  int current=-1;
  int end=-1;
  int size;
  int valuesIn;
};
#endif