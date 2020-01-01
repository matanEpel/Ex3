//
// Created by matan on 12/20/19.
//

#ifndef EX3__GENERALRESOURCES_H_
#define EX3__GENERALRESOURCES_H_

#include <map>
#include <string>
#include "Client.h"
#include "Server.h"

/*
 * this is a header file that handles all of the resources
 * that we want to be global to the whole program:
 */
extern map<string, Var*> symbolTable;
extern Server* server;
extern Client* client;
string tableToString();
bool conditionExist(double leftVal, double rightVal, string condition);
void clearTables();

#endif //EX3__GENERALRESOURCES_H_
