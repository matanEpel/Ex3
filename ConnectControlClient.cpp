//
// Created by matan on 12/19/19.
//

#include "ConnectControlClient.h"
#include "helpFromEx1.h"
#include "Client.h"
#include <string>
#include <iostream>
#include <map>

/*
 * the constructor:
 */
ConnectControlClient::ConnectControlClient(string port1, string ip1) {
  ConnectControlClient::port = (int)(toNumber(port1));
  ConnectControlClient::ip = ip1;
  type = "ConnectClient";
}

/*
 * executing the command. meaning - creating a new  client
 * and executing it's execute method:
 */
int ConnectControlClient::execute() {
  client = new Client(ConnectControlClient::port, ConnectControlClient::ip);
  client->execute(g_isReady, ConnectControlClient::terminate);
  delete client;

  return 1;
}

