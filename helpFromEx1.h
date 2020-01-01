//
// Created by matan on 11/4/19.
//

#ifndef DESKTOP_EX1_H
#define DESKTOP_EX1_H

using namespace std;

#include "Expression.h"
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>

/*
 * these are all the classes and methosds we used in ex1
 * so I am not documanting all over again since we know it is
 * working. I used it as a "black box".
 */

///general functions
bool isNumber(string numStr);
double toNumber(string numStr);
bool isLowerPrecedence(string op1, string op2);
///

class Variable: public Expression {
private:
    double varVal = 0;
    string name = "";

public:
    Variable(string name, double varVal);
    double calculate();

    ///got help from https://www.geeksforgeeks.org/types-of-operator-overloading-in-c/ in the ++/-- part
    Variable& operator++();
    Variable& operator--();

    Variable& operator+=(Variable& var2);
    Variable& operator-=(Variable& var2);
    Variable& operator+=(double val);
    Variable& operator-=(double val);

    Variable& operator++(int);
    Variable& operator--(int);

    string getName(){return this->name;}

    ~Variable(){};
};

class Value: public Expression {
private:
    double val = 0;

public:
    Value(double val);
    double calculate();
    ~Value(){};
};

///binary expressions:
class BinaryExpression: public Expression
{
protected:
    Expression* exp1;
    Expression* exp2;

public:
    virtual double calculate() = 0;
    ~BinaryExpression();
};

class Div: public BinaryExpression {
public:
    Div(Expression* exp1, Expression* exp2);
    double calculate() override;
};

class Mul: public BinaryExpression {
public:
    Mul(Expression* exp1, Expression* exp2);
    double calculate() override;
};

class Plus: public BinaryExpression {
public:
    Plus(Expression* exp1, Expression* exp2);
    double calculate() override;
};

class Minus: public BinaryExpression {
public:
    Minus(Expression* exp1, Expression* exp2);
    double calculate() override;
};

///binary expressions:
class UnaryExpression: public Expression
{
protected:
    Expression* exp;

public:
    double calculate() override = 0;
    ~UnaryExpression() override;
};

class UPlus: public UnaryExpression {
public:
    UPlus(Expression* exp);
    double calculate() override;
};

class UMinus: public UnaryExpression {
public:
    UMinus(Expression* exp);
    double calculate() override;
};

class Interpreter {
private:
    vector<Variable*> vars;
public:
    void setVariables(string vars);
    Expression* interpret(string exp);
    bool isVarHere(string varName);
    double getVarHere(string varName);
    ~Interpreter();
};

class Token {
private:

    bool isOperation = true;
    bool isVar = false;
    string operationOrVar;
    double val;
    Expression* valOrVar;
    bool isunary;
public:
    Token(double val);
    Token(bool isVar, string operationOrVar, bool isUnary);
    bool isNumOrVar(){return !this->isOperation;}
    bool isVal(){return !this->isVar;}
    double getVal();
    string getOp();
    void setExp(string var, double val);
    void setExp(double val);
    bool isUnary(){return this->isunary;}
};

///general functions:
void freeStack(stack<Expression*>* stack);
void freeStack(stack<Token*>* stack);
void freeQueue(queue<Token*>* queue);
bool isValidName(string varName);

#endif //DESKTOP_EX1_H
