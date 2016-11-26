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

    //Serializacion recursiva
    void serialize(json& jserialization){
        std::cout << "Serializo recursivamente Number: " << objectName << std::endl;

        json jReceiver;
        receiver->serialize(jReceiver);
        jserialization["receiver"] = jReceiver;
        jserialization["operation"] = operation;

        json jArgument;
        receiver->serialize(jArgument);
        jserialization["argument"] = jArgument;

        json jResult;
        receiver->serialize(jResult);
        jserialization["result"] = jResult;

        json jNativeValue;
        value.serialize(jNativeValue);
        jserialization["native"] = jNativeValue;

    }

    //Deserealizacion

    static Number* deserialize(json& jdeserialization, Lobby* lobby){
        Object* number = new Number();
        object->objectName = jdeserialization["objectName"];
        object->representation = jdeserialization["representation"];

        json jRegisterOfSlots;
        jRegisterOfSlots = jdeserialization["slots"];
        object->slots.deserialize(jRegisterOfSlots, object, lobby);

        json jMorph;
        jMorph = jdeserialization["myMorph"];
        object->myMorph.deserialize(jMorph);

        object->myLobby = lobby;

        return object;
    }

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
