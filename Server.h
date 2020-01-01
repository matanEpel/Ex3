//
// Created by matan on 12/20/19.
//

#ifndef EX3__SERVER_H_
#define EX3__SERVER_H_

#include <string>
#include "helpFromEx1.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "xmlData.h"
#include "Var.h"
#include "lock.h"

extern map<string, Var*> inSymbolTable;

list<double> bufferToList(string buff);

/*
 * this is a server class that handles all
 * the tasks of the server:
  */
class Server {
 private:
  int port;
 public:
  Server(int port1);
  int execute(bool& g_isReady, bool* terminate);
  void updateAllIn(list<double> vals, bool first);
  int sizeToEnter(char buffer[1024]);
  list<string> toLines(char buffer[1024]);
};
#endif //EX3__SERVER_H_
