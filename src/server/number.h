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

    //Serializacion TEST
    void serialize(json& jserialization){

        std::cout << "Object::serialize adentro de Number: " << objectName << std::endl;
        jserialization["objectName"] = objectName;
        jserialization["representation"] = representation;

        json jRegisterOfSlots;
        slots.serialize(jRegisterOfSlots);
        jserialization["slots"] = jRegisterOfSlots;

        json jMorph;
        myMorph.serialize(jMorph);
        jserialization["myMorph"] = jMorph;

        //Agrego lo de number

        std::cout << "Number::serialize" << std::endl;
        jserialization["operation"] = operation;
        json jNativeValue;
        value.serialize(jNativeValue);
        jserialization["nativeValue"] = jNativeValue;

        jserialization["type"] = "number";
    }

    //Deserealizacion TEST

    static Number* deserialize(json& jdeserialization, Lobby* lobby){
        std::cout << "Number::deserialize" << std::endl;
        Number* number = new Number();

        number->objectName = jdeserialization["objectName"];
        number->representation = jdeserialization["representation"];

        json jRegisterOfSlots;
        jRegisterOfSlots = jdeserialization["slots"];
        number->slots.deserialize(jRegisterOfSlots, number, lobby);

        json jMorph;
        jMorph = jdeserialization["myMorph"];
        number->myMorph.deserialize(jMorph);

        number->myLobby = lobby;

        //Agrego lo de number

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
