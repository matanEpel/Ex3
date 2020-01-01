//
// Created by matan on 12/19/19.
//

#include "DefineVarCommand.h"
#include "helpFromEx1.h"

/*
 * executing. meaning - defining a new variable and adding it to the
 * right symbol table:
 */
int DefineVarCommand::execute() {
  //stopping if somone is using the symbol table already:
  protectSymbolTable.lock();
  protectSymbolTable.unlock();

  //input is the variables values
  string valOrPath = (simOrVal)? DefineVarCommand::path : DefineVarCommand::path;
  Var* newVar = new Var(name, simOrVal, inOrOut, valOrPath);
  //adding to the symbol table while locking the mutex to protect it:
  protectSymbolTable.lock();
  symbolTable.insert(pair<string, Var*>(DefineVarCommand::name,newVar));
  protectSymbolTable.unlock();
  if(simOrVal && inOrOut)
  {
    protectSymbolTable.lock();
    inSymbolTable.insert(pair<string, Var*>(DefineVarCommand::path, newVar));
    protectSymbolTable.unlock();
  }
  return DefineVarCommand::simOrVal ? 3 : 2;
}

/*
 * the constructor to the define var command,
 * which handles the types of var accordingly to the "sim" direction: ->\<-
 */
DefineVarCommand::DefineVarCommand(string name1, bool simOrVal1, bool inOrOut1, string valOrPath1) {
  DefineVarCommand::simOrVal = simOrVal1;
  DefineVarCommand::name = name1;
  if(simOrVal)
  {
    DefineVarCommand::path = valOrPath1;
    DefineVarCommand::inOrOut = inOrOut1;
    DefineVarCommand::val = NULL;
  }
  else
  {
    DefineVarCommand::path = valOrPath1;
    DefineVarCommand::val = nullptr;
  }
}
