//
// Created by matan on 12/19/19.
//

#include <iostream>
#include "VarChanger.h"
#include "helpFromEx1.h"
#include "GeneralResources.h"

//a command that changes a variable
//and swnd a messege to the simulator if needE:
int VarChanger::execute() {
  protectSymbolTable.lock();
  protectSymbolTable.unlock();

  //calculating the var:
  Interpreter* i = new Interpreter();
  string vals = tableToString();
  i->setVariables(vals);
  Expression* expToCalc = i->interpret(VarChanger::exp);
  double val = expToCalc->calculate();

  //changing the symbol table if needed:
  protectSymbolTable.lock();
  if(val != symbolTable[VarChanger::varName]->getVal())
  {
    symbolTable[VarChanger::varName]->changeVal(val);
  }
  protectSymbolTable.unlock();

  protectSymbolTable.lock();
  //sending a command:
  client->addCommand("set " + symbolTable[VarChanger::varName]->getPath() + " " + to_string(val) + "\r\n");
  protectSymbolTable.unlock();

  delete i;
  return 2;
}

//constructor:
VarChanger::VarChanger(string name1, string exp1) {
  VarChanger::varName = name1;
  VarChanger::exp =  exp1;
}

