#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"
#include "nativevalue.h"
#include "object.h"
#include <map>


class Number : public Object{
private:
  std::string operation;
  NativeValue value;
public:

    //Serializacion recursiva
    void serialize(json& jserialization){
        std::cout << "Number::serialize" << std::endl;
        jserialization["operation"] = operation;
        json jNativeValue;
        value.serialize(jNativeValue);
        jserialization["nativeValue"] = jNativeValue;
    }

    //Deserealizacion

    static Number* deserialize(json& jdeserialization, Lobby* lobby){
        Number* number = new Number();
        number->operation = jdeserialization["operation"];
        number->value.deserialize(jdeserialization["nativeValue"]);
        return number;
    }

    Number();
    Number(int valueAux);
    ~Number();
    NativeValue convertToNativeValue();
    void setValue(int valueAux);
    NativeValue getValue();
    void setOperator(std::string operatorString);
    //void setReceiver(Object* receiverPtr);
    NativeValue ejecute(std::string operation, Object* expression);
    Object* clone();
    Object* getResult();
};

#endif
