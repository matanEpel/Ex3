//
// Created by matan on 12/19/19.
//

#ifndef EX3__DEFINEVARCOMMAND_H_
#define EX3__DEFINEVARCOMMAND_H_

#include <string>
#include "Command.h"
#include "Expression.h"
using namespace std;

/*
 * this command handles the definition of vars
 * that the sr entered in his code:
 */
class DefineVarCommand : public Command {
 private:
  string name;
  Expression* val;
  string path;
  bool simOrVal{};
  bool inOrOut;
 public:
  DefineVarCommand(string name1, bool simOrVal1, bool inOrOut1, string valOrPath1);
  int execute() override;

};

#endif //EX3__DEFINEVARCOMMAND_H_
