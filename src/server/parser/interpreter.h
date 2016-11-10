#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>
#include <map>

#include <string>
#include "../expression.h"
//#include "tuple_string.h"

class Interpreter{
private:
  std::map<std::string,int> mapMessages;
  std::stack<Expression*> stack;
  std::map<std::string,Expression*> map;
  void createNumber(std::string value);
  void assignationObject(std::string name);
  void addSlot(std::string name);
  void encapsulateStack();
  Expression* findObject(std::string name);
  void createExpression(std::string message);
  void sendMessage(std::string message);
public:
    Interpreter();
    void pushToken(std::string id,std::string message,std::string value);
    void interpretChar(char* buffer);
    void interpretFile(const char* nameFile);
    void end();
    ~Interpreter();
};

#endif /*INTERPRETER_H*/
