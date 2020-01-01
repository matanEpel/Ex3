//
// Created by matan on 12/19/19.
//

#include "IfCommand.h"
#include "helpFromEx1.h"

/*
 * this command executes all the command in the if condition
 * accorinly to the condition inside the if:
 */
int IfCommand::execute() {
  //stopping if the symbol table is in use:
  protectSymbolTable.lock();
  protectSymbolTable.unlock();

  //calculating the values of the expressin condition:
  string varVals = tableToString();
  Interpreter* i = new Interpreter();
  i->setVariables(varVals);
  double leftVal = (i->interpret(IfCommand::leftSide))->calculate();
  double rightVal = (i->interpret(IfCommand::rightSide))->calculate();
  if(conditionExist(leftVal, rightVal, IfCommand::condition))
  {
    //executing all the commands inside the of:
    for(Command* comm : IfCommand::listOfCommands)
    {
      comm->execute();
    }
  }
  return IfCommand::sizeOfScope;
}

/*
 * creating an if command";
 */
IfCommand::IfCommand(string left1, string condition1, string right1, int sizeOfScope1, list<Command*> listOfCommands1) {
  IfCommand::leftSide =  left1;
  IfCommand::rightSide =  right1;
  IfCommand::condition = condition1;
  IfCommand::sizeOfScope = sizeOfScope1;
  IfCommand::listOfCommands = listOfCommands1;
}
