// This is a basic program on C++
//
// Try to modify and run it and check out
// the output in the terminal below.
//
// Happy coding! :-)
// some stuff tomsee how git diff works

#include "CircularBuffer.h"
#include "CommandParser.h"
#include "MyStrings.h"

#include <iostream>

void CircularBufferTest();
void CommandParserTest();

int main() {
    CommandParserTest();
    CircularBufferTest();
    return 0;
}

void GetHeading(char *params)
{
  std::cout << "In GetHeading\n";
}

void SetHeading(char *params)
{
  float floats[1];
  ToFloat(params,floats);
  std::cout << "In SetHeading("<<floats[0]<<")\n";
}

void CommandParserTest()
{
  CommandParser p;
  p.Add(GetHeading,GETHEADING);
  p.Add(SetHeading,SETHEADING);
  char cmd1[] = "GetHeading()";
  p.Execute(cmd1);
  char cmd2[] = "SetHeading(60)";
  p.Execute(cmd2);
}

void CircularBufferTest()
{
  std::cout << "Created buffer of 10 floats, then added more than 10\n";
  CircularBuffer<float> cb;
  cb.SetSize(10);
  for (float i=1.1;i<20;i+=1.1)
    cb.Push(i);
  cb.Print();
}