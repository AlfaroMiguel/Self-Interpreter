#include "slot.h"

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