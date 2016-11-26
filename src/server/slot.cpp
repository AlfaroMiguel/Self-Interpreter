#include "slot.h"
#include "object.h"
#include "number.h"

Slot::Slot(){}

void Slot::serialize(json& jserialization){
    json jObject;
    if(objectReference)
        objectReference->serialize(jObject);
    jserialization["objectReference"] = jObject;
    jserialization["isMutable"] = isMutable;
    jserialization["isParent"] = isParent;
}

void Slot::serializeBase(json& jserialization){
    jserialization["objectReferenceID"] = objectReference->getMorphId();
    jserialization["isMutable"] = isMutable;
    jserialization["isParent"] = isParent;
}

void Slot::deserialize(json& jdeserialization, Lobby* lobby){
    std::cout << "Slot::deserialize start" << std::endl << jdeserialization.dump(4) << std::endl; //TODO sacar

    json jObject = jdeserialization["objectReference"];
    bool isSlotNumber = jObject["isNumber"];
    std::cout << isSlotNumber << std::endl;
    if(isSlotNumber) {
        std::cout << "Slot::deserialize slot number" << std::endl;
        this->objectReference = Number::deserialize(jObject, lobby);
    }
    else {
        std::cout << "Slot::deserialize slot object" << std::endl;
        this->objectReference = Object::deserialize(jObject, lobby);
    }
    this->isMutable = jdeserialization["isMutable"];
    this->isParent = jdeserialization["isParent"];

    std::cout << "Slot::deserialize end" << std::endl; //TODO sacar
}

Slot::Slot(Object* object, bool isMutable, bool esParent) :
objectReference(object), isMutable(isMutable), isParent(esParent){}

Slot::~Slot(){}

Object* Slot::getReference(){
    return objectReference;
}
bool Slot::isMutableSlot(){
    return this->isMutable;
}
bool Slot::isParentSlot(){
    return this->isParent;
}