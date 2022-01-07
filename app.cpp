// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
// add a comment
// and another comment

#include "CircularBuffer.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!\n";
    CircularBuffer<float> cb;
    cb.SetSize(5);
    for (float i=1.1;i<10;i+=1)
      cb.Push(i);
    cb.Print();
    return 0;
}
