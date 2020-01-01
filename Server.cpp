//
// Created by matan on 12/20/19.
//

#include <cstring>
#include "Server.h"

map<string, Var*> inSymbolTable;

/*
 * a command that runs the server with
 * 2 argumentsL one for terminsting the server and one for
 * telling the main thread that we have connected:
 */
int Server::execute(bool& g_isReady, bool* terminate) {
  //create socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    std::cerr << "Could not create a socket"<<std::endl;
  }

  //bind socket to IP address
  // we first need to create the sockaddr obj.
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
  address.sin_port = htons(port);
  //we need to convert our number
  // to a number that the network understands.

  //the actual bind command
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    std::cerr<<"Could not bind the socket to an IP"<<std::endl;
  }

  //making socket listen to the port
  if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
    std::cerr<<"Error during listening command"<<std::endl;
  } else{
    std::cout<<"Server is now listening ..."<<std::endl;
  }

  // accepting a client
  int client_socket = accept(socketfd, (struct sockaddr *)&address,
                             (socklen_t*)&address);

  if (client_socket == -1) {
    std::cerr<<"Error accepting client"<<std::endl;
  }

  close(socketfd); //closing the listening socket

  //reading from client
  char buffer[1024] = {0};
  read( client_socket , buffer, 1024);
  buffer[1023] = '\0';
  bool firstFirst = true;
  //translating the buffer into lines:
  list<string> listOfLinesFirst = toLines(buffer);
  for(string currLine : listOfLinesFirst)
  {
    list<double> valsList1 = bufferToList(currLine);
    (Server::updateAllIn)(valsList1, firstFirst);
    firstFirst = false;
  }

  //telling the main thread that we have connected:
  g_isReady = true;

  while(true)
  {
    //checking if we shold terminate:
    if(*terminate)
    {
      close(client_socket);
      return 2;
    }
    //reading from the client:
    char inWhileBuffer[1024] = {0};
    bool first = true;
    read( client_socket , inWhileBuffer, 1024);
    inWhileBuffer[1023] = '\0';
    list<string> listOfLines = toLines(inWhileBuffer);
    //updating the symbol table for each line:
    for(string currLine : listOfLines)
    {
      list<double> valsList1 = bufferToList(currLine);
      (Server::updateAllIn)(valsList1, first);
      first = false;
    }
  }
}

/*
 * a method for updating all the
 * vars in the symbol tabel:
 */
void Server::updateAllIn(list<double> vals, bool first)
{
  //if(!first || vals.size() == indexToPath.size())
  if(vals.size() == indexToPath.size() && (first || ! first))
  {
    int index = 0;
    for(double val : vals)
    {
      string path = '\"' + indexToPath[index] + '\"';
      //going through each val:
      if(inSymbolTable.find(path) != inSymbolTable.end())
      {
        protectSymbolTable.lock();
        inSymbolTable[path]->changeVal(val);
        protectSymbolTable.unlock();
      }

      index++;
    }
  }
}

/*
 * a method for converting a buffer into list:
 */
list<double> bufferToList(string buff)
{
  list<double> listOfVals;

  string builder = "";

  for(auto curr : buff)
  {
    //checking for special characters:
    if(curr == '\0' || curr == '\n' || curr == '\r' || curr == ',')
    {
      listOfVals.push_back(toNumber(builder));
      builder = "";
    }
    else
    {
      builder += curr;
    }
  }
  return listOfVals;
}

//constructor:
Server::Server(int port1) {
  Server::port = port1;
}

//a method for checking the amount of chars to the enter:
int Server::sizeToEnter(char *buffer) {
  int count = 0;
  while(buffer[count] != '\0' && buffer[count] != '\n' && count < 1024)
  {
    count++;
  }
  return count;
}

//chnverting the buffer into seprate lines:
list<string> Server::toLines(char *buffer) {
  list<string> lines;
  int i = 0;

  //going through all the biffer:
  while(i < 1024 && buffer[i] != '\0')
  {
    string currLine = "";
    while(buffer[i] != '\0' && buffer[i] != '\n' && i < 1024)
    {
      //adding the curr character:
      currLine += buffer[i];
      i++;

      if(i >= 1024)
      {
        break;
      }
    }
    currLine += "\n";
    lines.push_back(currLine);
    i++;
    if(i >= 1024)
    {
      break;
    }
  }

  return lines;
}
