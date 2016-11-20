#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"
#include "nativevalue.h"
#include "object.h"
#include <map>


class Number : public Object{
private:
  Object* receiver;
  std::string operation;
  Object* argument;
  Object* result;
  NativeValue value;
public:
    Number(int valueAux);
    ~Number();
    NativeValue convertToNativeValue();
    void setValue(int valueAux);
    NativeValue getValue();
    void setOperator(std::string operatorString);
    void setReceiver(Object* receiverPtr);
    NativeValue ejecute(std::string operation, Object* expression);
    Object* clone();
};

#endif
