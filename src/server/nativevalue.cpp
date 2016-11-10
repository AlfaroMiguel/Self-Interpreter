#include "nativevalue.h"
#include <stdexcept>


NativeValue::NativeValue(){
    isIntBool = false;
    isFloatBool = false;
    isBoolBool = false;
    isStringBool = false;
}

bool NativeValue::valueSetted(){
    return (isIntBool || isFloatBool || isBoolBool || isStringBool);
}


NativeValue::~NativeValue(){}


bool NativeValue::isInt(){
  return isIntBool;
}

bool NativeValue::isString(){
  return isStringBool;
}


bool NativeValue::isFloat(){
  return isFloatBool;
}

bool NativeValue::isBool(){
  return isBoolBool;
}

void NativeValue::setValue(int newValue){
  if(this->valueSetted())
    throw std::runtime_error("Valor ya seteado");
  intValue = newValue;
  isIntBool = true;
}

void NativeValue::setValue(float newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    floatValue = newValue;
    isFloatBool = true;
}

void NativeValue::setValue(bool newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    boolValue = newValue;
    isBoolBool = true;
}


void NativeValue::setValue(std::string newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    stringValue = newValue;
    isStringBool = true;
}

int NativeValue::getInt(){
    if(!isInt())
        throw std::runtime_error("El valor nativo no corresponde al tipo 'int'");
    return intValue;
}

float NativeValue::getFloat(){
    if(!isFloat())
        throw std::runtime_error("El valor nativo no corresponde al tipo 'float'");
    return floatValue;
}

bool NativeValue::getBool(){
    if(!isBool())
        throw std::runtime_error("El valor nativo no corresponde al tipo 'bool'");
    return boolValue;
}

std::string NativeValue::getString(){
    if(!isString())
        throw std::runtime_error("El valor nativo no corresponde al tipo 'string'");
    return stringValue;
}
