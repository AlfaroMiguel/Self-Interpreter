#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef SELFTP_SLOT_H
#define SELFTP_SLOT_H
class Lobby;
class Object;

#include <string>
/*Encapsula la informacion de un slot de self
 * Contiene la referencia al puntero del objeto
 * Y dos valores booleanos que indican si son mutables o parent slot*/
class Slot{
    Object* objectReference;
    bool isMutable;
    bool isParent;

public:

    //TEST SERIALIZATION

    void serialize(json& jserialization); //Definida en cpp
    void serializeBase(json& jserialization); //Definida en cpp
    void deserialize(json& jdeserialization, Lobby* lobby); //Definida en cpp

    /*Constructor vacio*/
    Slot();
    /*Constructor recibe la refernecia al objeto, si es mutable y parent*/
    Slot(Object* object, bool isMutable, bool isParent);
    /*Destructor de la clase Slot*/
    ~Slot();
    /*Devuelve la referencia al objeto que contiene*/
    Object* getReference();
    /*Devuelve si es mutable*/
    bool isMutableSlot();
    /*Devuelve si es parent slot*/
    bool isParentSlot();
};

#endif
