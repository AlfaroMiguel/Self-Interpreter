#include "nativevalue.h"
#include <stdexcept>

#include "object.h"

/*Modela un tipo generico que internamente puede ser un int, float o string*/
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

void NativeValue::serialize(json& jserialization){
    //std::cout << "NativeValue::serialize" << std::endl;

    jserialization["isIntBool"] = isIntBool;
    jserialization["isFloatBool"] = isFloatBool;
    jserialization["isBoolBool"] = isBoolBool;
    jserialization["isStringBool"] = isStringBool;

    if(isIntBool)jserialization["value"] = intValue;
    if(isFloatBool)jserialization["value"] = floatValue;
    if(isBoolBool)jserialization["value"] = boolValue;
    if(isStringBool)jserialization["value"] = stringValue;
}


void NativeValue::deserialize(json& jdeserialization){
    //std::cout << "NativeValue::deserialize start" << std::endl;
    std::cout << jdeserialization.dump(4) << std::endl;

    this->isIntBool = jdeserialization["isIntBool"];
    this->isFloatBool = jdeserialization["isFloatBool"];
    this->isBoolBool = jdeserialization["isBoolBool"];
    this->isStringBool = jdeserialization["isStringBool"];

    if(isIntBool)this->intValue = jdeserialization["value"];
    if(isFloatBool)this->floatValue = jdeserialization["value"];
    if(isBoolBool)this->boolValue = jdeserialization["value"];
    if(isStringBool)this->stringValue = jdeserialization["value"];

    //std::cout << "NativeValue::deserialize end" << std::endl;
}

bool NativeValue::isInt() const{
  return isIntBool;
}

bool NativeValue::isString() const{
  return isStringBool;
}


bool NativeValue::isFloat()const {
  return isFloatBool;
}

bool NativeValue::isBool()const {
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

int NativeValue::getInt() const{
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
