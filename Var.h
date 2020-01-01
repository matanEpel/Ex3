//
// Created by matan on 12/20/19.
//

#ifndef EX3__VAR_H_
#define EX3__VAR_H_

#include <string>
#include "Expression.h"

/*
 * a class of the var object
 * which stores variables that are used in the progrsam:
 */
class Var {
 private:
  string name;
  double val;
  string path;
  bool simOrVal;
  bool inOrOut;
 public:
  Var(string name1, bool simOrVal1, bool inOrOut1, string valOrPath1);
  string getName(){return name;}
  void changeVal(double val1);
  string getPath(){return path;}
  int getVal(){return val;}
  bool isOut(){return !inOrOut;}
  string removeEndings(string basic_string);
};

#endif //EX3__VAR_H_
