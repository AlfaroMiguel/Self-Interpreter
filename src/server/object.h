#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include "register_of_slots.h"
#include "nativevalue.h"

#include "morph.h"
class Lobby;

class Object{
protected:
    std::string objectName;
    RegisterOfSlots slots;
    std::string representation;
    Morph myMorph;
    Lobby* myLobby;

public:

    //Serializacion TEST

    //Serializacion recursiva
    virtual void serialize(json& jserialization){
        std::cout << "Object::serialize: " << objectName << std::endl;
        jserialization["objectName"] = objectName;
        jserialization["representation"] = representation;

        json jRegisterOfSlots;
        slots.serialize(jRegisterOfSlots);
        jserialization["slots"] = jRegisterOfSlots;

        json jMorph;
        myMorph.serialize(jMorph);
        jserialization["myMorph"] = jMorph;

        jserialization["type"] = "object";
    }

    //Deserealizacion

    static Object* deserialize(json& jdeserialization, Lobby* lobby){
        std::cout << "Object::deserialize start" << std::endl;
        Object* object = new Object();
        object->objectName = jdeserialization["objectName"];
        object->representation = jdeserialization["representation"];

        json jRegisterOfSlots;
        jRegisterOfSlots = jdeserialization["slots"];
        object->slots.deserialize(jRegisterOfSlots, object, lobby);

        json jMorph;
        jMorph = jdeserialization["myMorph"];
        object->myMorph.deserialize(jMorph);

        object->myLobby = lobby;

        std::cout << "Object::deserialize end" << std::endl;

        return object;
    }

    //Metodo TEST serchForId

    Object* searchForId(int objectId){
        std::cout << "Busco " << objectId << " en " << this->getName() << std::endl;
        std::cout << "Busco " << objectId << " mi ID: " << this->getMorphId() << std::endl;
        if(this->getMorphId() == objectId)return this;
        std::vector<Object*> mySlotsObjects = this->slots.getObjectsWhitoutParents(); //Para que no haya ciclos de busqueda
        for(auto itObjectSlot = mySlotsObjects.begin(); itObjectSlot != mySlotsObjects.end(); itObjectSlot++){
            if((*itObjectSlot)->getName() != "self") {
                Object *objectFound = (*itObjectSlot)->searchForId(objectId);
                if (objectFound != nullptr) return objectFound;
            }
        }
        return nullptr;
    }

    Object();
    Object(const Object& otherObject);
    virtual ~Object();

    Object* getSlotName(const std::string& name) const;


    RegisterOfSlots getParentsSlots() const;
    Object* searchObject(const std::string& name, Object *object);

    virtual void setReceiver(Object* receiverPtr){
      std::cout << "Object::setReceiver:" << std::endl;
    }
    virtual void setOperator(std::string operatorString){
      std::cout << "Object::setOperator:" << std::endl;
    }
    virtual void setArgument(Object* argumentPtr){
      std::cout << "Object::setArgument:" << std::endl;
    }
    virtual void setResult(Object* resultPtr){
      std::cout << "Object::setName:"<< std::endl;
    }
    virtual NativeValue getValue();
    virtual Object* getResult();
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);
    virtual void evaluate();

    void setName(const std::string newName);
    std::string getName() const;

    virtual std::vector<Object*> getReferences();
    RegisterOfSlots getSlots();
    virtual void addSlots(std::string slotName, Object* object, bool isMutable, bool isParentSlot);
    void RemoveSlots(std::string slotName);

    virtual Object* clone() const;
    virtual std::string getRepresentation() const;
    virtual void setRepresentation(const std::string representationString);
    virtual Object* print(const std::vector<Object*>& argumnets);

    //Object* collect(); Esto va en el Lobby

    void setLobby(Lobby* lobby);
    void notifyClients(std::string eventName, std::string clientName = "");
    void moveMorph(const std::string clientName, double newX, double newY);
    int getMorphId();
    void changeMorphName(std::string& newName);
};

#endif
