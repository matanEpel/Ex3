//
// Created by matan on 12/19/19.
//

#ifndef EX3_CMAKE_BUILD_DEBUG_PRINTCOMMAND_H_
#define EX3_CMAKE_BUILD_DEBUG_PRINTCOMMAND_H_

#include <string>
#include <list>
#include "Command.h"
#include "Expression.h"
using namespace std;

/*
 * a command that print string
 * or expressions:
 */
class PrintCommand : public Command {
  string toPrint;
 public:
  PrintCommand(string toPrint1);
  int execute() override;
};

#endif //EX3_CMAKE_BUILD_DEBUG_PRINTCOMMAND_H_
