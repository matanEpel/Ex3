//
// Created by matan on 12/19/19.
//

#ifndef EX3__OPENSERVERCOMMAND_H_
#define EX3__OPENSERVERCOMMAND_H_

#include <string>
#include <condition_variable>
#include "Command.h"
using namespace std;

/*
 * a class that handeling the command
 * of opening a data server:
 */
class openServerCommand : public Command{
 private:
  int port;
 public:
  openServerCommand(string port1);
  int execute() override;
};

#endif //EX3__OPENSERVERCOMMAND_H_
