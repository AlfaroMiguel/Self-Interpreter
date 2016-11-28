#include "number.h"
#include <iostream> //cout //stof
#include "nativevalue.h"
#include "object.h"
#include <string>

Number::Number() : Object() {}

Number::Number(int valueAux) : Object() {
    setName(std::to_string(valueAux));
    setRepresentation(std::to_string(valueAux));
    value.setValue(valueAux);
}

Number::~Number() {}


Object *Number::clone() {
    int valueInt = value.getInt();
    Number *newNumber = new Number(valueInt);
    setName(this->getName());
    return newNumber;
}

void Number::setValue(int valueAux) {}

Object *Number::getResult() {
    return this;
}

NativeValue Number::getValue() {
    return value;
}

void Number::setOperator(std::string operatorString) {
    this->operation = operatorString;
}


NativeValue Number::convertToNativeValue() {
    return getValue();
}

NativeValue Number::ejecute(std::string operation, Object *expression) {
    /*Aca permito cosas del tipo 3 + 4.0*/
    int resultado = 0;
    if (expression->getValue().isInt() || expression->getValue().isFloat()) {
        if (operation.compare("*") == 0) {
            resultado = value.getInt() * expression->getValue().getInt();
        } else {
            resultado = value.getInt() + expression->getValue().getInt();
        }
    } else {
        std::cout << "Number::ejecute() cannot aplicate operation" << operation << "NativeValue is not typeCorrect"
                  << std::endl;
    }
    NativeValue value;
    value.setValue(resultado);
    return value;
}


void Number::serialize(json &jserialization) {
    jserialization["objectName"] = objectName;
    jserialization["representation"] = representation;

    json jRegisterOfSlots;
    slots.serialize(jRegisterOfSlots);
    jserialization["slots"] = jRegisterOfSlots;

    json jMorph;
    myMorph.serialize(jMorph);
    jserialization["myMorph"] = jMorph;

    //Agrego lo de number

    jserialization["operation"] = operation;
    json jNativeValue;
    value.serialize(jNativeValue);
    jserialization["nativeValue"] = jNativeValue;

    jserialization["type"] = "number";

}

Number *Number::deserialize(json &jdeserialization, Lobby *lobby) {
    Number *number = new Number();

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
