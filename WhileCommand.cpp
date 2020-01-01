//
// Created by matan on 12/19/19.
//

#include "WhileCommand.h"
#include "helpFromEx1.h"

int WhileCommand::execute() {
  protectSymbolTable.lock();
  protectSymbolTable.unlock();

  //calcuating the values of the expressions:
  string varVals = tableToString();
  Interpreter* i = new Interpreter();
  i->setVariables(varVals);
  double leftVal = (i->interpret(WhileCommand::leftSide))->calculate();
  double rightVal = (i->interpret(WhileCommand::rightSide))->calculate();
  //running the command:
  while(conditionExist(leftVal, rightVal, WhileCommand::condition))
  {
    for(Command* comm : WhileCommand::listOfCommands)
    {
      comm->execute();
    }

    //calcuating the values of the expressions:
    Interpreter* i1 = new Interpreter();
    /////////////////////////////
    protectSymbolTable.lock();
    protectSymbolTable.unlock();
    varVals = tableToString();
    i1->setVariables(varVals);
    leftVal = (i1->interpret(WhileCommand::leftSide))->calculate();
    rightVal = (i1->interpret(WhileCommand::rightSide))->calculate();

    delete i1;
  }

  delete i;
  return WhileCommand::sizeOfScope;
}


//constructor:
WhileCommand::WhileCommand(string left, string condition1, string right, int sizeOfScope1, list<Command*> listOfCommands1) {
  WhileCommand::leftSide = left;
  WhileCommand::rightSide = right;
  WhileCommand::condition = condition1;
  WhileCommand::sizeOfScope = sizeOfScope1;
  WhileCommand::listOfCommands = listOfCommands1;
}

