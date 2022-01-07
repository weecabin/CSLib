
#ifndef FIFO_H
#define FIFO_H
#include "CircularBuffer.h"

template<class T> class Fifo
{
  public:
  Fifo(int size)
  {
    buffer.SetSize(size);
  }
  bool IsFull()
  {
    return buffer.Full();
  }
  bool IsEmpty()
  {
    return buffer.Empty();
  }
  void Push(T value)
  {
    buffer.Push(value);
  }
  void Add(T value)
  {
    buffer.Push(value);
  }
  T Pop()
  {
    if (buffer.Empty())
      throw;
    T retval = buffer.Tail();
    buffer.Delete(buffer.ValuesIn());
    return retval;
  }
  void Print()
  {
    buffer.Print();
  }
  private:
  CircularBuffer<T> buffer;
};
#endif