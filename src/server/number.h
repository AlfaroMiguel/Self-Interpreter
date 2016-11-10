#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"
#include "nativevalue.h"
#include <map>

class Number : public Expression{
private:
  std::map<std::string,Expression*> slots;
  NativeValue value;
public:
    Number(int valueAux);
    ~Number();
    void setValue(int valueAux);
    NativeValue getValue();
    NativeValue ejecute(std::string operation, Expression* expression);
    void evaluate();
};

#endif
