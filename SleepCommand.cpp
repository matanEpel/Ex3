//
// Created by matan on 12/19/19.
//

#include "SleepCommand.h"

//a command that sllepsin the curr thread
//which in our case is the main:
int SleepCommand::execute() {
  protectSymbolTable.lock();
  protectSymbolTable.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(SleepCommand::toSleep));
  return 1;
}

//constructor:
SleepCommand::SleepCommand(string toSleep1) {
  SleepCommand::toSleep = (int)(toNumber(toSleep1));
}
