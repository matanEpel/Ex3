//
// Created by matan on 12/19/19.
//

#ifndef EX3__SLEEPCOMMAND_H_
#define EX3__SLEEPCOMMAND_H_

#include <string>
#include <list>
#include "Command.h"
#include "Expression.h"
#include "helpFromEx1.h"
#include <chrono>
#include <thread>

using namespace std;

/*
 * a command used to make the
 * curr thread to sleep:
 */
class SleepCommand : public Command {
  int toSleep;
 public:
  SleepCommand(string toSleep1);
  int execute() override;
};

#endif //EX3__SLEEPCOMMAND_H_
