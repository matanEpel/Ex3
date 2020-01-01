//
// Created by matan on 12/20/19.
//
#include "GeneralResources.h"


map<string, Var*> symbolTable;
Server* server;
Client* client;

/*
 * this functions clears the symbol table:
 */
void clearTables()
{
  for(auto val : symbolTable)
  {
    delete val.second;
  }
}

/*
 * this function converts the symbol table to
 * a string which cand be read ny the interpreter:
 */
string tableToString()
{
  protectSymbolTable.lock();
  stringstream stringBuilder;

  for(auto var : symbolTable)
  {
    //building the string of the current var:
    stringBuilder<<var.first;
    stringBuilder<<"=";
    stringBuilder<<var.second->getVal();
    stringBuilder<<";";
  }

  protectSymbolTable.unlock();

  return stringBuilder.str();
}

/*
 * a function for checking if a condition symbol exists
 * in the list of legal symbols and if is a valid symbol:
 */
bool conditionExist(double leftVal, double rightVal, string condition) {
  if (condition == "==") {
    return leftVal == rightVal;
  } else if (condition == "<=") {
    return leftVal <= rightVal;
  } else if (condition == ">=") {
    return leftVal >= rightVal;
  } else if (condition == "<") {
    return leftVal < rightVal;
  } else if (condition == ">") {
    return leftVal > rightVal;
  } else if (condition == "!=") {
    return leftVal != rightVal;
  }
  cout<<"eror with condition";
  return false;
}