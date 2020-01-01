//
// Created by matan on 12/20/19.
//

#include "Var.h"
#include "helpFromEx1.h"
#include "GeneralResources.h"

//changing the val of a var:
void Var::changeVal(double val1) {
  Var::val = val1;
}

//constructor:
Var::Var(string name1, bool simOrVal1, bool inOrOut1, string valOrPath1) {
  Var::simOrVal = simOrVal1;
  Var::name = name1;
  //checking the type of var we have:
  if(simOrVal)
  {
    Var::path = removeEndings(valOrPath1);
    Var::inOrOut = inOrOut1;
    Var::val = 0;
  }
  else
  {
    Var::path = "";

    Interpreter* i = new Interpreter();

    //calculating it's curr value:
    i->setVariables(tableToString());
    Var::val =  (i->interpret(valOrPath1))->calculate();

    delete i;
  }
}

//removes all the ":
string Var::removeEndings(string basic_string) {
  stringstream stringBuilder;
  for(char c : basic_string)
  {
    if(c != '\"')
    {
      stringBuilder<<c;
    }
  }
  return stringBuilder.str();
}
