#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"
#include "nativevalue.h"
#include "object.h"
#include <map>


class Number : public Object{
private:
  NativeValue value;
public:
    Number(int valueAux);
    ~Number();
    NativeValue convertToNativeValue();
    void setValue(int valueAux);
    NativeValue getValue();
    NativeValue ejecute(std::string operation, Expression* expression);
    void evaluate();
};

#endif
