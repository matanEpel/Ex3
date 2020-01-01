//
// Created by matan on 12/19/19.
//

#include "helpFromEx1.h"
#include "openServerCommand.h"
#include <string>

//opening a new server:
int openServerCommand::execute() {
  //creating a server:
  server = new Server(port);
  //runing the server:
  server->execute(g_isReady, openServerCommand::terminate);
  delete server;

  return 2;
}

//creating a "openServer" command:
openServerCommand::openServerCommand(string port1) {
  openServerCommand::port = (int)(toNumber(port1));
  type = "OpenServer";
}
