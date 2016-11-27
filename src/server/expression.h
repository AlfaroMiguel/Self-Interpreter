#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <string>
#include "nativevalue.h"
#include "searcher_object.h"

class Expression:public Object{
    Object* receiver;
    std::string operation;
    Object* argument;
    Object* result;
public:
    virtual void serialize(json& jserialization);
    static Expression* deserialize(json& jdeserialization, Lobby* lobby);

    Expression();
    ~Expression();
    /*Sets*/
    void setReceiver(Object* receiverPtr);
    void setOperator(std::string operatorString);
    void setArgument(Object* argumentPtr);
    void setResult(Object* resultPtr);
    std::vector<Object*> getReferences();
    std::string getRepresentation() const ;
    virtual NativeValue getValue();
    Object* getResult();
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);
    virtual void evaluate();
    Object* clone()
;};

#endif
