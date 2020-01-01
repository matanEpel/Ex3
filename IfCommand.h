//
// Created by matan on 12/19/19.
//

#ifndef EX3__IFCOMMAND_H_
#define EX3__IFCOMMAND_H_

#include <string>
#include <list>
#include "Command.h"
#include "Expression.h"
using namespace std;

/*
 * this is the if commands. the if inherits from
 * command and it is used to execute commands under certain conditions;
 */
class IfCommand : public Command {
  string leftSide;
  string condition;
  string rightSide;
  list<Command*> listOfCommands;
  int sizeOfScope;
 public:
  IfCommand(string left1, string condition1, string right1, int sizeOfScope1, list<Command*> listOfCommands1);
  int execute() override;

};

#endif //EX3__IFCOMMAND_H_
