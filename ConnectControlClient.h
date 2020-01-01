//
// Created by matan on 12/19/19.
//

#ifndef EX3__CONNECTCONTROLCLIENT_H_
#define EX3__CONNECTCONTROLCLIENT_H_

#include "Command.h"
#include <string>
#include <condition_variable>
#include <list>
#include <map>

using namespace std;
class Command;

/*
 * this is a command which creates
 * a new client accordingly to the data the usr entered.
 */
class ConnectControlClient : public Command{
 private:
  int port;
  string ip;
  list<string> commandsToSend;
 public:
  ConnectControlClient(string port1, string ip1);
  int execute() override;
};

#endif //EX3__CONNECTCONTROLCLIENT_H_
