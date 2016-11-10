#ifndef NATIVEVALUE_H
#define NATIVEVALUE_H

#include <string>

class NativeValue{
private:
    int intValue;
    float floatValue;
    bool boolValue;
    std::string stringValue;

    bool isIntBool, isFloatBool, isBoolBool, isStringBool;
    bool valueSetted();

public:
    NativeValue();
    ~NativeValue();
    void setValue(int newValue);
    void setValue(float newValue);
    void setValue(bool newValue);
    void setValue(std::string newValue);
    bool isInt();
    bool isFloat();
    bool isBool();
    bool isString();
    int getInt();
    float getFloat();
    bool getBool();
    std::string getString();
};
#endif
