#include "nativevalue.h"
<<<<<<< HEAD
#include <stdexcept>
bool NativeValue::valueSetted(){
    return (isIntBool || isFloatBool || isBoolBool || isStringBool);
}

NativeValue::NativeValue(){
    isIntBool = false;
    isFloatBool = false;
    isBoolBool = false;
    isStringBool = false;
=======

bool NativeValue::valueSetted(){
    return (isInt || isFloat || isBool || isString);
}

NativeValue::NativeValue() : Object(){
    isInt = false;
    isFloat = false;
    isBool = false;
    isString = false;
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
}

NativeValue::~NativeValue(){}

<<<<<<< HEAD

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
=======
void NativeValue::setValue(int newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    intValue = newValue;
    isInt = true;
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
}

void NativeValue::setValue(float newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    floatValue = newValue;
<<<<<<< HEAD
    isFloatBool = true;
=======
    isFloat = true;
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
}

void NativeValue::setValue(bool newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    boolValue = newValue;
<<<<<<< HEAD
    isBoolBool = true;
}


=======
    isBool = true;
}

>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
void NativeValue::setValue(std::string newValue){
    if(this->valueSetted())
        throw std::runtime_error("Valor ya seteado");
    stringValue = newValue;
<<<<<<< HEAD
    isStringBool = true;
}

int NativeValue::getInt(){
    if(!isInt())
=======
    isString = true;
}

int NativeValue::getInt(){
    if(!isInt)
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
        throw std::runtime_error("El valor nativo no corresponde al tipo 'int'");
    return intValue;
}

float NativeValue::getFloat(){
<<<<<<< HEAD
    if(!isFloat())
=======
    if(!isFloat)
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
        throw std::runtime_error("El valor nativo no corresponde al tipo 'float'");
    return floatValue;
}

bool NativeValue::getBool(){
<<<<<<< HEAD
    if(!isBool())
        throw std::runtime_error("El valor nativo no corresponde al tipo 'bool'");
=======
    if(!isBool)
        throw std::runtime_error::("El valor nativo no corresponde al tipo 'bool'");
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
    return boolValue;
}

std::string NativeValue::getString(){
<<<<<<< HEAD
    if(!isString())
=======
    if(!isString)
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
        throw std::runtime_error("El valor nativo no corresponde al tipo 'string'");
    return stringValue;
}
