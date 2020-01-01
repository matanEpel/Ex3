//
// Created by matan on 12/20/19.
//

#ifndef EX3__CLIENT_H_
#define EX3__CLIENT_H_

#include <string>
#include <list>
#include <map>
#include "Var.h"
#include "helpFromEx1.h"
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mutex>
#include "lock.h"

using namespace std;

/*
 * this class handles all of the tasks of the client, incluf=ding:
 * connecting to the simulator, sending commands etc.
 */
class Client {
 private:
  int port;
  string ip;
  list<string> commandsToSend;
 public:
  Client(int port1, string ip1);
  int execute(bool& g_isReady, bool* terminate);
  void addCommand(string command);
};

#endif //EX3__CLIENT_H_
