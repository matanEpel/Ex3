//
// Created by matan on 11/4/19.
//

#include "helpFromEx1.h"

/*
 * these are all the classes and methosds we used in ex1
 * so I am not documanting all over again since we know it is
 * working. I used it as a "black box".
 */
/////////////////////////////////////////////
///general functions:
///checking if the varName is valid:
bool isValidName(string varName)
{
  if(!isalpha(varName[0]))
  {
    return false;
  }
  for(unsigned int i = 1; i < varName.size(); i++)
  {
      if(!isalpha(varName[i]) && varName[i] != '_' && !isdigit(varName[i]))
      {
        return false;
      }
  }
  return true;
}
void freeStack(stack<Expression*>* stack)
{
  while(!(stack->empty()))
  {
    delete stack->top();
    stack->pop();
  }
  delete stack;
}
void freeStack(stack<Token*>* stack)
{
  while(!(stack->empty()))
  {
    delete stack->top();
    stack->pop();
  }
  delete stack;
}
void freeQueue(queue<Token*>* queue)
{
  while(!(queue->empty()))
  {
    delete queue->front();
    queue->pop();
  }
  delete queue;
}
/////////////////////////////////////////////

bool isOperator(const char &i);
/////////////////////////////////////////////
///all the binaryExpression method's implementations:
BinaryExpression::~BinaryExpression()
{
    delete this->exp1;
    delete this->exp2;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the unaryExpression method's implementations:
UnaryExpression::~UnaryExpression()
{
    delete this->exp;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Variable method's implementations:
Variable::Variable(string name1, double varVal1)
{
    this->name = name1;
    this->varVal = varVal1;
}

double Variable::calculate()
{
    return this->varVal;
}

Variable& Variable::operator++(){
    this->varVal++;
    return *this;
}

Variable& Variable::operator--(){
    this->varVal--;
    return *this;
}

Variable& Variable::operator+=(Variable& var2){
    this->varVal += var2.calculate();
    return *this;
}

Variable& Variable::operator-=(Variable& var2){
    this->varVal -= var2.calculate();
    return *this;
}

Variable& Variable::operator++(int){
    this->operator++();
    return *this;
}

Variable& Variable::operator--(int){
    this->operator--();
    return *this;
}

Variable& Variable::operator-=(double val) {
    this->varVal -= val;
    return *this;
}

Variable& Variable::operator+=(double val) {
    this->varVal += val;
    return *this;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Value method's implementations:
Value::Value(double val1)
{
    this->val = val1;
}

double Value::calculate()
{
    return this->val;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Mul method's implementations:
Mul::Mul(Expression* exp11, Expression* exp22)
{
    this->exp1 = exp11;
    this->exp2 = exp22;
}

double Mul::calculate()
{
    return this->exp1->calculate()*this->exp2->calculate();
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Div method's implementations:
Div::Div(Expression* exp11, Expression* exp22)
{
    this->exp1 = exp11;
    this->exp2 = exp22;
}

double Div::calculate()
{
    if(this->exp2->calculate() == 0)
    {
        throw "bad input";
    }
    else
    {
        return this->exp1->calculate()/this->exp2->calculate();
    }
}
///////////////////////////////////

/////////////////////////////////////////////
///all the Plus method's implementations:
Plus::Plus(Expression* exp11, Expression* exp22)
{
    this->exp1 = exp11;
    this->exp2 = exp22;
}

double Plus::calculate()
{
    return this->exp1->calculate()+this->exp2->calculate();
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Minus method's implementations:
Minus::Minus(Expression* exp11, Expression* exp22)
{
    this->exp1 = exp11;
    this->exp2 = exp22;
}

double Minus::calculate()
{
    return this->exp1->calculate()-this->exp2->calculate();
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the UMinus method's implementations:
UMinus::UMinus(Expression* exp1)
{
    this->exp = exp1
        ;
}

double UMinus::calculate()
{
    return -this->exp->calculate();
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the UMinus method's implementations:
UPlus::UPlus(Expression* exp1)
{
    this->exp = exp1;
}

double UPlus::calculate()
{
    return this->exp->calculate();
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Interpreter method's implementations:
Token::Token(double val1)
{
    this->val = val1;
    this->isOperation = false;
}

Token::Token(bool isVar1, string operationOrVar1, bool isUnary1)
{
    this->operationOrVar = operationOrVar1;
    this->isunary = isUnary1;
    this->isVar = isVar1;
    this->isOperation = !isVar1;
    if(this->isVar && !isValidName(operationOrVar1))
    {
      //throw "bad input";
    }
}

string Token::getOp()
{
    return this->operationOrVar;
}

double Token::getVal()
{
    return this->val;
}

void Token::setExp(double val1) {
    this->valOrVar = new Value(val1);
}

void Token::setExp(string var, double val1) {
    this->valOrVar = new Variable(var, val1);
}

bool isLowerPrecedence(string op1, string op2)
{
    if(op1 == "-" || op1 == "+")
    {
        if(op2 == "*" || op2 == "/" )
        {
            return true;
        }
    }
    return false;
}
/////////////////////////////////////////////

/////////////////////////////////////////////
///all the Interpreter method's implementations:
bool isNumber(string numStr)
{
    string::const_iterator iter = numStr.begin();
    ///checking if there is only digits (or - in the beginning):
    if((*iter) == '-' || isdigit(*iter)){
        do{
            iter++;
        }while(isdigit(*iter));
        ///checking if there is only digits after the period:
        if((*iter) == '.'){
            do{
                iter++;
            }while(isdigit(*iter));
        }
        else if(iter == numStr.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    ///checking if we finished all the string without any problem:
    if(iter == numStr.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

double toNumber(string numStr){
    double num = 0;
    bool minus = false;
    string::const_iterator iter = numStr.begin();
    if(iter < numStr.end())
    {
      if ((*iter) == '-') {
        minus = true;
      } else {
        ///converting to int:
        num += (*iter) - '0';
      }
      iter++;
    }
    if(iter < numStr.end())
    {
      while (iter != numStr.end() && isdigit(*iter)) {
        num *= 10;
        ///converting to int:
        num += (*iter) - '0';
        iter++;
        if (iter == numStr.end()) {
          break;
        }
      }
    }
    ///checking if there is only digits after the period:
    if(iter < numStr.end())
    {
      if((*iter) == '.'){
        iter++;
        double afterThePeriod = 1;
        while(isdigit(*iter) && iter != numStr.end())
        {
          afterThePeriod /= 10;
          num += ((*iter) - '0')*afterThePeriod;
          iter++;
        }
      }
    }
    if(minus){
        return -num;
    }
    return num;
}

void Interpreter::setVariables(string vars1)
{

    stringstream strStream(vars1);
    string token;
    ///parsing the string:
    while(getline(strStream, token, ';'))
    {
        stringstream varStream(token);
        string tokenPart;
        vector<string> parts;
        ///geyying the 2 parts of the example=example expressions:
        while(getline(varStream, tokenPart, '='))
        {
            parts.push_back(tokenPart);
        }

        ///checking that there is indeed 2 parts:
        if(parts.size() == 2)
        {
            if(isNumber(parts.back()))
            {
                this->vars.push_back(new Variable(parts.front(),toNumber(parts.back())));
            }
            else
            {
                throw "bad input";
            }
        }
        else
        {
            throw "bad input";
        }
    }
}

queue<Token*>* createPostfix(string exp)
{
    queue<Token*>* tokenQueue = new queue<Token*>();
    stack<Token*>* operationStack = new stack<Token*>();
    queue<Token*>* outputQueue = new queue<Token*>();

    string::const_iterator iter = exp.begin();

    ///creating queue of all the tokens:
    while(iter != exp.end())
    {
        bool minusNumFlag = false;
        string currDigit;
        ///checking a case of number with minus:
        if((*iter) == '-' && !isdigit((*(iter-1))) && !isalpha((*(iter-1))) && ('_' != ((*(iter-1)))))
        {
            ++iter;
            ///calculating the number digits:
            while((*iter) != '+' && (*iter) != '-' && (*iter) != '*' && (*iter) != '/' &&
                  (*iter) != '(' && (*iter) != ')')
            {
                currDigit += (*iter);
                ++iter;
            }
            if(currDigit.size() == 0)
            {
                --iter;
            }
            else
            {
                minusNumFlag = true;
                currDigit = "-"+currDigit;
            }
        }
        ///calculating in case of non minus number:
        if(!minusNumFlag)
        {
            while((*iter) != '+' && (*iter) != '-' && (*iter) != '*' && (*iter) != '/' &&
                  (*iter) != '(' && (*iter) != ')' && iter != exp.end())
            {
                currDigit += (*iter);
                ++iter;
            }
        }
        ///creating new token according to if hee is a number, var or operation:
        if(isNumber(currDigit))
        {
            double num = toNumber(currDigit);
            Token* numToken = new Token(num);
            tokenQueue->push(numToken);
        }
        else if (currDigit != "")
        {
            tokenQueue->push(new Token(true, currDigit, false));
        }
        else
        {
            bool isUnary = false;
            string op;
            op += (*iter);
            if('('==(*(iter+1)) && ((op == "-") | (op == "+")) && (tokenQueue->size() == 0 || !(tokenQueue->back()->isNumOrVar())))
            {
              isUnary = true;
            }
            tokenQueue->push(new Token(false, op, isUnary));
            ++iter;
        }
    }

    ///running the ‫‪Shunting-yard‬‬ algorithm to create a postfix notation of the expression:
    while(tokenQueue->size() != 0)
    {
        Token* currTok = tokenQueue->front();
        tokenQueue->pop();

        if(currTok->isNumOrVar())
        {
            outputQueue->push(currTok);
        }
        else if (currTok->getOp() != "(" && currTok->getOp() != ")")
        {
            while(operationStack->size() != 0 && isLowerPrecedence(currTok->getOp(), operationStack->top()->getOp()))
            {
                outputQueue->push(operationStack->top());
                operationStack->pop();
            }
            operationStack->push(currTok);
        }
        else if (currTok->getOp() == "(")
        {
            operationStack->push(currTok);
        }
        else if (currTok->getOp() == ")")
        {
            while((operationStack->size() != 0) && (operationStack->top()->getOp()!="("))
            {
                outputQueue->push(operationStack->top());
                operationStack->pop();
            }
            if(operationStack->size() != 0)
            {
                delete operationStack->top();
                operationStack->pop();
            }
            else
            {
                freeStack(operationStack);
                freeQueue(tokenQueue);
                throw "bad input";
            }
            delete currTok;
        }
        else
        {
          freeStack(operationStack);
          freeQueue(tokenQueue);
            throw "bad input";
        }


    }

    while(operationStack->size()!=0)
    {
        outputQueue->push(operationStack->top());
        operationStack->pop();
    }

    ///deleting the used stack and queue:
    while(!tokenQueue->empty())
    {
        delete tokenQueue->front();
        tokenQueue->pop();
    }
    delete tokenQueue;

    while(!operationStack->empty())
    {
        delete operationStack->top();
        operationStack->pop();
    }
    delete operationStack;

    return outputQueue;
}

Expression* Interpreter::interpret(string exp11)
{
    queue<Token*>* postfixQueue = createPostfix(exp11);
    stack<Expression*>* evaluateStack = new stack<Expression*>();
    Expression* interpretedExp;

    ///evaluating the expression using the postfix queue:
    while(postfixQueue->size()!=0)
    {
        if(postfixQueue->front()->isNumOrVar())
        {
            if(postfixQueue->front()->isVal())
            {
                evaluateStack->push(new Value(postfixQueue->front()->getVal()));
            }
            else
            {
                string op = postfixQueue->front()->getOp();
                if(this->isVarHere(op))
                {
                  ///////////////////////////
                    evaluateStack->push(new Variable(op, this->getVarHere(op)));
                }
                ///checking the case where we have -ExamleVar:
                else if(op[0] == '-' && (op).size() >= 2 &&
                        this->isVarHere((op).substr(1,(op).size()-1)))
                {
                    evaluateStack->push(new Variable((op).substr(1,(op).size()-1),
                                 (-1)*this->getVarHere((op).substr(1,(op).size()-1))));
                }
                else
                {
                    freeStack(evaluateStack);
                    freeQueue(postfixQueue);
                    throw "bad input";
                }

            }
        }
        else
        {
            if(postfixQueue->size()==0)
            {
              freeStack(evaluateStack);
              freeQueue(postfixQueue);
              throw "bad input";
            }
            ///checking the case of UMinus or UPlus:
            else if(postfixQueue->front()->isUnary())
            {
                string operation = postfixQueue->front()->getOp();
                char op = operation[0];
                Expression* exp = evaluateStack->top();
                evaluateStack->pop();
                switch (op)
                {
                    case '-':
                        evaluateStack->push(new UMinus(exp));
                        break;
                    case '+':
                        evaluateStack->push(new UPlus(exp));
                        break;
                    default:
                        freeStack(evaluateStack);
                        freeQueue(postfixQueue);
                        throw "bad input";
                }
            }
            ///checking all the regular operation cases:
            else if (evaluateStack->size() > 1)
            {
                string operation = postfixQueue->front()->getOp();
                Expression* exp1 = evaluateStack->top();
                evaluateStack->pop();
                Expression* exp2 = evaluateStack->top();
                evaluateStack->pop();
                switch (operation[0])
                {
                    case '/':
                        evaluateStack->push(new Div(exp2, exp1));
                        break;
                    case '*':
                        evaluateStack->push(new Mul(exp1, exp2));
                        break;
                    case '-':
                        evaluateStack->push(new Minus(exp2, exp1));
                        break;
                    case '+':
                        evaluateStack->push(new Plus(exp1, exp2));
                        break;
                    default:
                        delete exp1;
                        delete exp2;
                        freeStack(evaluateStack);
                        freeQueue(postfixQueue);
                        throw "bad input";
                }
            }
            else
            {
                freeStack(evaluateStack);
                freeQueue(postfixQueue);
                throw "bad input";
            }
        }
        delete postfixQueue->front();
        postfixQueue->pop();
    }
    interpretedExp = evaluateStack->top();
    ///deleting the used stack and queue:
    while(!postfixQueue->empty())
    {
        delete postfixQueue->front();
        postfixQueue->pop();
    }
    delete postfixQueue;

    while(evaluateStack->size() > 1)
    {
        delete evaluateStack->top();
        evaluateStack->pop();
    }
    delete evaluateStack;

    return interpretedExp;
}

bool Interpreter::isVarHere(string varName) {
    for(Variable* currVar : this->vars )
    {
        if(currVar->getName() == varName)
        {
            return true;
        }
    }

    return false;
}

double Interpreter::getVarHere(string varName) {
    double val = 0;
    for(Variable* currVar : this->vars)
    {
        if(currVar->getName() == varName)
        {
            val = currVar->calculate();
        }
    }

    return val;
}

Interpreter::~Interpreter()
{
    for(Variable* var : this->vars)
    {
        delete var;
    }
    this->vars.clear();
}

/////////////////////////////////////////////