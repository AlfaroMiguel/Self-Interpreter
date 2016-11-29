#include "slot.h"
#include "object.h"
#include "number.h"
#include "expression.h"

Slot::Slot(){}

void Slot::serialize(json& jserialization){
    json jObject;
    if(objectReference)
        objectReference->serialize(jObject);
    jserialization["objectReference"] = jObject;
    jserialization["isMutable"] = isMutable;
    jserialization["isParent"] = isParent;
}

void Slot::deserialize(json& jdeserialization, Lobby* lobby){
    json jObject = jdeserialization["objectReference"];
    std::string typeString = jObject["type"];
    if(typeString == "number") {
        this->objectReference = Number::deserialize(jObject, lobby);
    }
    else if (typeString == "expression"){
        this->objectReference = Expression::deserialize(jObject, lobby);
    }
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