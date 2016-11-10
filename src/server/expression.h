#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <string>
#include "nativevalue.h"

class Expression{
    Expression* receiver;
    std::string operation;
    Expression* argument;
    Expression* result;
    std::string name;
    std::map<std::string,Expression*> mySlots;
public:
    Expression();
    void setReceiver(Expression* receiverPtr);
    void setOperator(std::string operatorString);
    void setArgument(Expression* argumentPtr);
    void setName(std::string nameStr);
    void setResult(Expression* resultPtr);
    virtual NativeValue getValue();
    Expression* getSlot();
    Expression* getResult();
    void addSlots(std::string id,Expression* slot, bool algo, bool otro);
    std::string getName();
    virtual NativeValue ejecute(std::string operationStr, Expression* argumentPtr);
    virtual void evaluate();
    ~Expression();
};

#endif
