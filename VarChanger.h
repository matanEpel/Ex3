//
// Created by matan on 12/19/19.
//

#ifndef EX3__VARCHANGER_H_
#define EX3__VARCHANGER_H_

#include "Command.h"
#include "Expression.h"

//a class that handles all the aspects of
//variables changing:
class VarChanger : public Command {
 private:
  string varName;
  string exp;
 public:
  explicit VarChanger(string name1, string exp1);
  int execute() override;
};

#endif //EX3__VARCHANGER_H_
