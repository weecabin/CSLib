#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "Map1.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "MyDefines.h"

using namespace std;
/*
ToFloat
helper tool to convert the parameter string CommandParser passes to the call back function
to an array of floats.
*/
void ToFloat(char *params, float floats[])
{
  int len = sizeof(*floats);
  char *token = strtok(params,",");
  int i = 0;
  while (token != NULL)
  {
    floats[i++]=atof(token);
    if (i>=len)break;
    token = strtok(NULL,",");
  }
}

/*
ToInt
helper tool to convert the parameter string CommandParser passes to the call back function
to an array of ints.
*/
void ToInt(char *params, int ints[])
{
  int len = sizeof(*ints);
  char *token = strtok(params,",");
  int i = 0;
  while (token != NULL)
    {
    ints[i++]=atoi(token);
    if (i>=len)break;
    token = strtok(NULL,",");
    }
}

class CommandHandler
{
  public:
  CommandHandler(void (*executer)(char *),const char* cmd)
  {
    this->executer=executer;
    this->cmd=cmd;
  }
  void Execute(char *cmdLine)
  {
    executer(cmdLine);
  }
  const char* cmd;
  private:
  void (*executer)(char *);
};

/* Command Parser
parses a command lines, and executes callback functions to handle commands defined in its map.
Start by adding a command string and a function pointer that will handle the command.
Add as many as you like.
The callback function has the following signature
void FunctionName(char *parameters)
void FunctionName()
*/
class CommandParser
{
  public:
  CommandParser()
  {
  }
  ~CommandParser()
  {
    for(auto itr=cmdMap.begin();itr!=cmdMap.end();++itr)
    {
      delete *itr;
    }
  };
  // adds the executer function with cmd as the key to the command map
  void Add(void (*executer)(char *),const char* cmd)
  {
    CommandHandler *handler=new CommandHandler(executer,cmd);
    cmdMap.Insert(cmd,handler);
  }

  void Print()
  {
    cmdMap.Print();
  }

  // Execute...
  // if the command exists, executes the associated callback with the parameter
  // string as the function parameter.
  bool Execute(char *cmdLine)
  {
    char *cmd = strtok(cmdLine,"(");
    //print("\nexecute: ");println(cmd);
    if (cmd == NULL)return false;
    auto itr = cmdMap.begin()[cmd];
    if (itr!=cmdMap.end()) // the key esists
    {
      #ifdef DEBUG 
      print("Execute found ");println((*itr)->cmd);
      #endif
      char *params = strtok(NULL,")");
      if (params!=NULL)
      {
        (*itr)->Execute(params);
      }
      else
      {
        char nothing[]="";
        (*itr)->Execute(nothing);
      }
    }
    return true;
  }

  private:
  Map1<const char*,CommandHandler *> cmdMap;
  //Map1<const char*,CommandHandler *,LessChar,EqualChar> cmdMap;
};

#endif