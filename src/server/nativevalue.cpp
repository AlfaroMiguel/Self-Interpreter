#include "nativevalue.h"

bool NativeValue::valueSetted(){
    return (isInt || isFloat || isBool || isString);
}

NativeValue::NativeValue() : Object(){
    isInt = false;
    isFloat = false;
    isBool = false;
    isString = false;
}

NativeValue::~NativeValue(){}

void NativeValue::setValue(int newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    intValue = newValue;
    isInt = true;
}

void NativeValue::setValue(float newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    floatValue = newValue;
    isFloat = true;
}

void NativeValue::setValue(bool newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    boolValue = newValue;
    isBool = true;
}

void NativeValue::setValue(std::string newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    stringValue = newValue;
    isString = true;
}

int NativeValue::getInt(){
    if(!isInt)
        throw std::runtime_error("El valor nativo no corresponde al tipo 'int'");
    return intValue;
}

float NativeValue::getFloat(){
    if(!isFloat)
        throw std::runtime_error("El valor nativo no corresponde al tipo 'float'");
    return floatValue;
}

bool NativeValue::getBool(){
    if(!isBool)
        throw std::runtime_error::("El valor nativo no corresponde al tipo 'bool'");
    return boolValue;
}

std::string NativeValue::getString(){
    if(!isString)
        throw std::runtime_error("El valor nativo no corresponde al tipo 'string'");
    return stringValue;
}
