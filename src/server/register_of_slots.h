#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef REGISTEROFSLOTS_H
#define REGISTEROFSLOTS_H

#include "slot.h"
#include <iostream>
#include <map>
#include <vector>

class Object;
/*Clase encargada de contener todos los slots de un objeto.
 * Contiene un map donde la clave es el nombre del slot y el valor es el objeto Slot
 * que lo representa. Se encarga de resolver toda la logica que se necesita con respecto
 * a los slots de un objeto*/
class RegisterOfSlots{
    std::map<std::string,Slot> slotMap;
public:
    //TEST SERIALIZATION

    void serialize(json& jserialization){
        for(auto itSlot = slotMap.begin(); itSlot != slotMap.end(); itSlot++) {
            json jSlot;
            if (itSlot->first != "self") {
                std::cout << "Serializo (REC) el slot: " << itSlot->first << std::endl;
                itSlot->second.serialize(jSlot);
                jserialization.push_back(std::make_pair(itSlot->first, jSlot));
            }
        }
    }

    void serializeBase(json& jserialization){
        for(auto itSlot = slotMap.begin(); itSlot != slotMap.end(); itSlot++) {
                json jSlot;
                std::cout << "Serializo (BASE) el slot: " << itSlot->first << std::endl;
                itSlot->second.serializeBase(jSlot);
                jserialization.push_back(std::make_pair(itSlot->first, jSlot));
        }
    }

    /*Constructor, inicialmente el slotMap esta vacio*/
    RegisterOfSlots();
    /*Destructo, no se libera ningun recurso*/
    ~RegisterOfSlots();
    /*Recibe el nombre de un slot, la referencia al objeto que representa, un valor booleano
     * que indica si es mutable y otro que indica si es parent slot.
     * Crea el slot y lo agrega al registro*/
    void addSlot(const std::string& slotName, Object *object, bool isMutable, bool isParent);
    /*Recibe el nombre de un slot y devuelve el slot si se encuentra*/
    Slot getSlot(const std::string &slotName) const;
    /*Recibe el nombre de un slot y lo elimina del registro*/
    void removeSlot(const std::string &slotName);
    /*Devuelve otro registro de slots pero con los parents slots encontrados*/
    RegisterOfSlots getParentsSlots() const;
    /*Recibe el nombre de un slot, y el puntero a un objeto, busca el slot en este objeto
     * realizando el respectivo lookup en los parents slots devuelve la referencia al objeto si lo encontro
     * Lanza excepcion si se encontro mas de un slot o ninguno en el objeto llamado de esa manera*/
    Object* searchSlot(const std::string &slotName, Object *object);
    /*Obtiene todos los objetos que se encuentran en el registro de slots*/
    std::vector<Object*> getObjects();
    /*Obtiene los objetos que no son parents slots del registro de slots*/
    std::vector<Object*> getObjectsNotParent();
};

#endif
