//
// Created by matan on 12/22/19.
//

#ifndef EX3__LOCK_H_
#define EX3__LOCK_H_

#include <mutex>

//a global mutex for protecting the symbol table:
extern std::mutex protectSymbolTable;

#endif //EX3__LOCK_H_
