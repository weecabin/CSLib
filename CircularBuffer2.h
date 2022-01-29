#ifndef CIRCULARBUFFER2_H
#define CIRCULARBUFFER2_H

#include "MyDefines.h"
#include <stdexcept>

/*
CircularBuffer
Implements a buffer with a maximum size of size elements.
from the outside, new elements appear to be added at the beginning of
the buffer, and older elements are pushed down. if the newest element 
exceeds the buffer size, the oldest will be removed.
the array operator [0] returns the most recent addition, or the Head of the buffer.

The difference between this and CircularBuffer is this version
uses indexes to manage the buffer whereas CircularBuffer uses pointers.
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
    head=tail=-1;
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
    if (valuesIn==0)tail=0;
    if (++valuesIn>size)
      valuesIn=size;
    if (++head>=size)
      head=0;
    AdjustEnd();
    buffer[head]=value;
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
    if (d>=valuesIn)return; // can't insert past the tail
    for (int i=valuesIn==size?valuesIn-2:valuesIn-1;i>=d;i--)
    {
      buffer[Index(i+1)]=buffer[Index(i)];
    }
    buffer[Index(d)]=value;
    if (valuesIn==size)return;
    valuesIn++;
    AdjustEnd();
  }

  void Delete(int d)
  {
    for (int i=d;i<valuesIn-1;i++)
    {
      buffer[Index(i)]=buffer[Index(i+1)];
    }
    valuesIn--;
    AdjustEnd();
    return;
  }

  T operator[](int i)
  {
    if (valuesIn==0)
      throw std::invalid_argument( "List is empty" );
    if (i>=size)
      i=i%size;
    return buffer[Index(i)];
  }

  // removes and returns the oldest value 
  T PopTail()
  {
    if (valuesIn==0)
      throw std::invalid_argument( "List is empty" );
    T temp = buffer[tail];
    valuesIn--;
    if (++tail>=size)
      tail=0;
    return temp;
  }

  // removes and returns the newest value
  T PopHead()
  {
    if (valuesIn==0)
      throw std::invalid_argument( "List is empty" );
    T temp = buffer[head];
    valuesIn--;
    if (--head<0)
      head=size-1;
    AdjustEnd();
    return temp;
  }

  private:
  void AdjustEnd()
  {
    if (valuesIn==0)
    { 
      head=tail=-1;
      return;
    }
    tail=head-valuesIn+1;
    if (tail<0)
      tail=size-1;
  }

  int Index(int i)
  {
    int temp=head-i;
    if (temp>=0)
      return temp;
    temp+=size;
    return temp;
  }

  T *buffer=nullptr;
  T *invalid=nullptr; 
  int head=-1; // the index into the buffer of the last pushed value
  int tail=-1; // the index into the buffer of the oldest value
  int size;
  int valuesIn;
};
#endif