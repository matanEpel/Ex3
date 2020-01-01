//
// Created by matan on 12/18/19.
//

#ifndef EX3__LEXER_H_
#define EX3__LEXER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

/*
 * this is the class of the lexer, which
 * handles the parsing of the text file:
 */
class lexer {
  string fileName;
  list<string> tokensList;

 public:
  lexer(string file);
  static string removeSpaces(string line);
  string isSpecialCharacter(string line,unsigned int& currLocation);
  list<string> execute();
};

#endif //EX3__LEXER_H_
