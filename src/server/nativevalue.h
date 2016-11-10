<<<<<<< HEAD
#ifndef NATIVEVALUE_H
#define NATIVEVALUE_H

#include <string>

class NativeValue{
=======
#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"
#include "method.h"

class NativeValue : public Object{
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
private:
    int intValue;
    float floatValue;
    bool boolValue;
    std::string stringValue;

<<<<<<< HEAD
    bool isIntBool, isFloatBool, isBoolBool, isStringBool;
=======
    bool isInt, isFloat, isBool, isString;
>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
    bool valueSetted();

public:
    NativeValue();
    ~NativeValue();
<<<<<<< HEAD
=======

>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
    void setValue(int newValue);
    void setValue(float newValue);
    void setValue(bool newValue);
    void setValue(std::string newValue);
<<<<<<< HEAD
    bool isInt();
    bool isFloat();
    bool isBool();
    bool isString();
=======

>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
    int getInt();
    float getFloat();
    bool getBool();
    std::string getString();
};
<<<<<<< HEAD
=======

>>>>>>> 0a66430639a31b2d5bc350d30bd796138792f662
#endif
