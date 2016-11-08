#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"
#include "method.h"

class NativeValue : public Object{
private:
    int intValue;
    float floatValue;
    bool boolValue;
    std::string stringValue;

    bool isInt, isFloat, isBool, isString;
    bool valueSetted();

public:
    NativeValue();
    ~NativeValue();

    void setValue(int newValue);
    void setValue(float newValue);
    void setValue(bool newValue);
    void setValue(std::string newValue);

    int getInt();
    float getFloat();
    bool getBool();
    std::string getString();
};

#endif
