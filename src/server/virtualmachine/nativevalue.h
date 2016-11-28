#ifndef JSON_LIB
#define JSON_LIB

#include "../../common/json.hpp"

using json = nlohmann::json;
#endif


#ifndef NATIVEVALUE_H
#define NATIVEVALUE_H

#include <string>

class NativeValue {
private:
    int intValue;
    float floatValue;
    bool boolValue;
    std::string stringValue;
    /*Flags para identificar el tipo*/
    bool isIntBool, isFloatBool, isBoolBool, isStringBool;

    bool valueSetted();

public:
    //Metodo para serializar un NativeValue
    void serialize(json &jserialization);

    //Metodo para deserializar un NativeValue
    void deserialize(json &jdeserialization);

    //Constructor del NativeValue, internamente puede ser un string, un bool,
    //float o un int
    NativeValue();

    ~NativeValue();

    /*Se setea el valor del NativeValue,en caso de que ya haya sido seteado
    anteriormente, se lanza un error, no se puede setear con 2 tipos distintos*/
    void setValue(int newValue);

    void setValue(float newValue);

    void setValue(bool newValue);

    void setValue(std::string newValue);

    /*Metodos para indicar a qué tipo corresponde internamente*/
    bool isInt();

    bool isFloat();

    bool isBool();

    bool isString();

    /*Metodos para obtener el dato interno, en caso de NativeValue no corresponda
    con el tipo que se está pidiendo, se lanza un erro*/
    int getInt();

    float getFloat();

    bool getBool();

    std::string getString();
};

#endif
