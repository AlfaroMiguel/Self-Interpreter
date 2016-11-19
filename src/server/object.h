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
#include "lobby.h"

class Object{
protected:
    std::string objectName;
    RegisterOfSlots slots;
    std::string representation;
    Morph myMorph;
    Lobby* myLobby;

public:
    Object();
    Object(const Object& otherObject);
    virtual ~Object();

    Object* getSlotName(std::string name);
    virtual void isObject();


    RegisterOfSlots getParentsSlots();
    Object* searchObject(std::string name, Object *object);

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
    std::string getName();


    RegisterOfSlots getSlots();
    void addSlots(std::string slotName, Object* object, bool isMutable, bool isParentSlot);
    void RemoveSlots(std::string slotName);

    Object* clone();
    virtual std::string getRepresentation() const;
    virtual void setRepresentation(std::string representationString);
    virtual Object* print(const std::vector<Object*>& argumnets);

    //Object* collect(); Esto va en el Lobby

    void setLobby(Lobby* lobby);
    void notifyClients(std::string eventName, std::string clientName = "");
    void moveMorph(std::string clientName, double newX, double newY);
    int getMorphId();
};

#endif
