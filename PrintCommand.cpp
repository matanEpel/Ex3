//
// Created by matan on 12/19/19.
//

#include <iostream>
#include "PrintCommand.h"

//executing = printing what's inside the print command:
int PrintCommand::execute() {
  protectSymbolTable.lock();
  protectSymbolTable.unlock();
  //printing regulary in case of regular string to print:
  if((PrintCommand::toPrint)[0] == '\"')
  {
    cout<<PrintCommand::toPrint<<"\n";
  }
  else
  {
    //calculating the expression inside the print command:
    Interpreter* i = new Interpreter;
    i->setVariables(tableToString());
    double valToPrint = (i->interpret(toPrint))->calculate();
    cout<<(PrintCommand::toPrint)<<"="<<to_string(valToPrint)<<"\n";
    delete i;
  }
  return 1;
}

//creating a print commad:
PrintCommand::PrintCommand(string toPrint1) {
  PrintCommand::toPrint = toPrint1;
}

