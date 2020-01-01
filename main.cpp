#include <iostream>
#include "lexer.h"
#include "Command.h"
#include "openServerCommand.h"
#include "ConnectControlClient.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "VarChanger.h"
#include <list>
#include <thread>
#include <zconf.h>
#include <map>

list<Command*> createCommands(string arrayOfTokens[], int start, int end);
int countTillEndOfScope(int currLocation, string arrayOfTokens[]);

void clearCommands(list<Command*> listOfCommands);
using namespace std;

int main(int argc, char* argv[]) {
  //checking if number of arguments is ik:
  if(argc > 4)
  {
    throw "bad arguments";
  }
  string fileName = argv[1];
  openServerCommand* servercomm;
  ConnectControlClient* clientComm;
  list<Command*> listOfCommands;
  lexer myLexer(fileName);

  //getting the list of tokens:
  list<string> list = myLexer.execute();
  string* arrayOfTokens = new string[list.size()];
  int i = 0;
  bool terminate = false;

  //converting to array:
  for(string token : list)
  {
    arrayOfTokens[i] = token;
    i++;
  }


  //creating all the commands from the file using the token list:
  listOfCommands = createCommands(arrayOfTokens, 0, list.size());

  //opening the server:
  servercomm = (openServerCommand*)(*listOfCommands.begin());
  servercomm->terminate = &terminate;
  thread serverThread([=] {(servercomm)->execute(); });
  //waiting until the server is connected:
  while ((servercomm)->g_isReady == false)
  {
    sleep(1);
  }
  listOfCommands.pop_front();

  //opening the client:
  clientComm = (ConnectControlClient*)(*(listOfCommands.begin()));
  clientComm->terminate = &terminate;
  thread clientThread([=] {(clientComm)->execute(); });

  //waiting until the client is connacted:
  while ((clientComm)->g_isReady == false)
  {
    sleep(1);
  }
  listOfCommands.pop_front();

  for(auto comm : listOfCommands)
  {
    comm->execute();
  }

  terminate = true;

  serverThread.join();
  clientThread.join();

  //deleting all allocated memory:
  clearTables();
  delete[] arrayOfTokens;
  delete clientComm;
  delete servercomm;
  clearCommands(listOfCommands);
  return 0;
}

/*
 * a function to clear all the commands we
 * want to send to the simulator:
 * */

void clearCommands(list<Command*> listOfCommands) {
  for(auto comm : listOfCommands)
  {
    delete comm;
  }
}

/*
 * counting the amount of tokens
 * until the end of the current sscope":
 */
int countTillEndOfScope(int currLocation, string arrayOfTokens[])
{
  int count = 0;
  int countOfScopeStart = 1;
  //while ther eis still an open "{":
  while(countOfScopeStart > 0)
  {
    //we are in the end of the current scpoe:
    if(arrayOfTokens[currLocation] == "}")
    {
      countOfScopeStart--;
      if(countOfScopeStart > 0)
      {
        currLocation++;
        count++;
      }
    }
    else
    {
      if(arrayOfTokens[currLocation] == "{")
      {
        countOfScopeStart++;
      }
      currLocation++;
      count++;
    }
  }
  return count;
}

//creating the list of commands from the tokens list:
list<Command*> createCommands(string arrayOfTokens[], int start, int end)
{
  list<Command*> listOfCommands;
  int currIndex = 0;
  //runing through all the tokens:
  for(currIndex = start; currIndex < end; currIndex++)
  {
    string currToken = arrayOfTokens[currIndex];
    //checking each case of command, while adding the right commad:
    if(currToken == "openDataServer")
    {
      currIndex++;
      string port = arrayOfTokens[currIndex];
      listOfCommands.push_back(new openServerCommand(port));
    }
    else if(currToken == "connectControlClient")
    {
      currIndex++;
      string ip = arrayOfTokens[currIndex];
      currIndex++;
      string port = arrayOfTokens[currIndex];
      listOfCommands.push_back(new ConnectControlClient(port, ip));
    }
    else if(currToken == "var")
    {
      if(arrayOfTokens[currIndex+3] == "sim")
      {
        //checking which type of var it is:
        if(arrayOfTokens[currIndex+2] == "<-")
        {
          string name = arrayOfTokens[++currIndex];
          currIndex += 3;
          string path = arrayOfTokens[currIndex];
          listOfCommands.push_back(new DefineVarCommand(name, true, true, path));
        }
        else
        {
          string name = arrayOfTokens[++currIndex];
          currIndex += 3;
          string path = arrayOfTokens[currIndex];
          listOfCommands.push_back(new DefineVarCommand(name, true, false, path));
        }
      }
      else
      {
        string name = arrayOfTokens[++currIndex];
        currIndex += 2;
        string val = arrayOfTokens[currIndex];
        listOfCommands.push_back(new DefineVarCommand(name, false, false, val));
      }
    }
    else if(currToken == "Print")
    {
      currIndex++;
      string toPrint = arrayOfTokens[currIndex];
      listOfCommands.push_back(new PrintCommand(toPrint));
    }
    else if(currToken == "while")
    {
      string left = arrayOfTokens[++currIndex];
      string condition = arrayOfTokens[++currIndex];
      string right = arrayOfTokens[++currIndex];
      currIndex += 2;

      //checking the scope size:
      int scope = countTillEndOfScope(currIndex, arrayOfTokens);
      //creating the list of commands inside the while recursivly:
      list<Command*> commandsInWhile = createCommands(arrayOfTokens, currIndex, currIndex + scope);
      currIndex += scope;

      listOfCommands.push_back(new WhileCommand(left, condition, right, scope, commandsInWhile));
    }
    else if(currToken == "if")
    {
      string left = arrayOfTokens[++currIndex];
      string condition = arrayOfTokens[++currIndex];
      string right = arrayOfTokens[++currIndex];
      currIndex += 2;

      //checking the scope size:
      int scope = countTillEndOfScope(currIndex, arrayOfTokens);
      //creating the list of commands inside the while recursivly:
      list<Command*> commandsInIf = createCommands(arrayOfTokens, currIndex, currIndex + scope);
      currIndex += scope;

      listOfCommands.push_back(new IfCommand(left, condition, right, scope, commandsInIf));
    }
    else if(currToken == "Sleep")
    {
      currIndex++;
      string toSleep = arrayOfTokens[currIndex];
      listOfCommands.push_back(new SleepCommand(toSleep));
    }
    else
    {
      //otherwise it must be a variable:
      listOfCommands.push_back(new VarChanger(currToken, arrayOfTokens[currIndex + 2]));
      currIndex += 2;
    }

  }

  return listOfCommands;
}