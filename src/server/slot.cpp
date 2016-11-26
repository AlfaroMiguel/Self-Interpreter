#include "slot.h"
#include "object.h"

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
    json jObject = jdeserialization["objectReference"];
    this->objectReference = Object::deserialize(jObject, lobby);
    this->isMutable = jdeserialization["isMutable"];
    this->isParent = jdeserialization["isParent"];
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