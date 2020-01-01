//
// Created by matan on 12/19/19.
//

#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_

#include <string>
#include <condition_variable>
#include <map>
#include "Var.h"
#include "Client.h"
#include "Server.h"
#include "GeneralResources.h"

using namespace std;

/*
 * this is an interface which all commands
 * such as: sleep, while, if etc. will inherit from.
 */
class Command {
 public:
  bool g_isReady = false;
  bool* terminate = &g_isReady; //defult val
  bool continueOutside = false;
  string type = "regular";
  virtual int execute() = 0;
  virtual ~Command() {}
};

#endif //EX3__COMMAND_H_
