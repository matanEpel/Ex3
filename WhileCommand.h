//
// Created by matan on 12/19/19.
//

#ifndef EX3__WHILECOMMAND_H_
#define EX3__WHILECOMMAND_H_

#include <string>
#include <list>
#include "Command.h"
#include "Expression.h"
using namespace std;

/*
 * a command that handles while
 * loop and runs all the commands inside:
 */
class WhileCommand : public Command {
  string leftSide;
  string condition;
  string rightSide;
  list<Command*> listOfCommands;
  int sizeOfScope;
 public:
  WhileCommand(string left, string condition1, string right, int sizeOfScope1, list<Command*> listOfCommands1);
  int execute() override;

};

#endif //EX3__WHILECOMMAND_H_
