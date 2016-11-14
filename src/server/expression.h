#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <string>
#include "nativevalue.h"
#include "object.h"

class Expression:public Object{
    Object* receiver;
    std::string operation;
    Object* argument;
    Object* result;
public:
    Expression();
    ~Expression();
    void isObject();
    /*Sets*/
    void setReceiver(Object* receiverPtr);
    void setOperator(std::string operatorString);
    void setArgument(Object* argumentPtr);
    void setResult(Object* resultPtr);
    virtual NativeValue getValue();
    Object* getResult();
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);
    virtual void evaluate();
};

#endif
