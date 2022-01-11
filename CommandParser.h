#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include <map>
#include <cstring>
#include <cstdlib>
#include <iostream>

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
  private:
  void (*executer)(char *);
  const char* cmd;
};

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcasecmp(a, b) < 0;
   }
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
    map<const char*,CommandHandler *>::iterator it;
    for (it = cmdMap.begin(); it != cmdMap.end(); it++)
    {
      delete it->second;
    }
  };
  // adds the executer function with cmd as the key to the command map
  void Add(void (*executer)(char *),const char* cmd)
  {
    CommandHandler *handler=new CommandHandler(executer,cmd);
    cmdMap.insert({cmd,handler});
  }

  // Execute...
  // if the command exists, executes the associated callback with the parameter
  // string as the function parameter.
  bool Execute(char *cmdLine)
  {
    char *cmd = strtok(cmdLine,"(");
    if (cmd == NULL)return false;
    if (cmdMap.count(cmdLine)>0) // the key esists
    {
      char *params = strtok(NULL,")");
      if (params!=NULL)
      {
        cmdMap[cmd]->Execute(params);
      }
      else
      {
        char nothing[]="";
        cmdMap[cmd]->Execute(nothing);
      }
    }
    return true;
  }

  private:
  map<const char*,CommandHandler *, cmp_str> cmdMap;
};

#endif