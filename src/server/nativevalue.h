#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif


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

    void serialize(json& jserialization){
        std::cout << "NativeValue::serialize" << std::endl;
        jserialization["isIntBool"] = isIntBool;
        jserialization["isFloatBool"] = isFloatBool;
        jserialization["isBoolBool"] = isIntBool;
        jserialization["isStringBool"] = isStringBool;
        if(isIntBool)jserialization["value"] = intValue;
        if(isFloatBool)jserialization["value"] = floatValue;
        if(isBoolBool)jserialization["value"] = boolValue;
        if(isStringBool)jserialization["value"] = stringValue;
    }

    void deserialize(json& jdeserialization){
        std::cout << "NativeValue::deserialize" << std::endl;
        this->isIntBool = jdeserialization["isIntBool"];
        this->isFloatBool = jdeserialization["isFloatBool"];
        this->isBoolBool = jdeserialization["isBoolBool"];
        this->isStringBool = jdeserialization["isStringBool"];
        if(isIntBool)intValue = jdeserialization["value"];
        if(isFloatBool)floatValue = jdeserialization["value"];
        if(isBoolBool)boolValue = jdeserialization["value"];
        if(isStringBool)stringValue = jdeserialization["value"];
    }

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
