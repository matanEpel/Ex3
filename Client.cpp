//
// Created by matan on 12/20/19.
//

#include "Client.h"

/*
 * adding a command to send to the server:
 */
void Client::addCommand(string command) {
  (Client::commandsToSend).push_back(command);
}

/*
 * the main thread of the client
 * which handles the commands sending:
 */
int Client::execute(bool& g_isReady, bool* terminate) {
  //create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    //error
    std::cerr << "Could not create a socket"<<std::endl;
    return -1;
  }

  //We need to create a sockaddr obj to hold address of server
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;//IP4
  address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
  address.sin_port = htons(Client::port);
  //we need to convert our number (both port & localhost)
  // to a number that the network understands.

  // Requesting a connection with the server on local host with port 8081
  int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
  if (is_connect == -1) {
    std::cerr << "Could not connect to host server"<<std::endl;
    return -2;
  } else {
    std::cout<<"Client is now connected to server" <<std::endl;
  }
  g_isReady = true;

  //the main loop that handles the commands sending:
  while(true)
  {

    //in case we want to terminate the program, this part will take care of doing it memory-safe:
    if(*terminate)
    {
      close(client_socket);
      return 2;
    }
    //protecting the symbol tan]ble using mutx:
    protectSymbolTable.lock();
    //sending all the command in the list of commands we got from the user's code:
    for(string command : Client::commandsToSend)
    {
      if(command != "")
      {

        int is_sent = send(client_socket , command.c_str() , command.size() , 0 );
        if (is_sent == -1) {
          std::cout<<"Error sending message"<<std::endl;
        }
      }
    }
    (Client::commandsToSend).clear();
    protectSymbolTable.unlock();
  }
}

/*
 * client constructor:
 */
Client::Client(int port1, string ip1) {
  Client::port = port1;
  Client::ip = ip1;
}
