#include "slot.h"

Slot::Slot(Object* objeto, bool esMutable, bool esParent) :
objeto(objeto), esMutable(esMutable), esParent(esParent){}

Slot::~Slot(){}

Object* Slot::obtenerReferencia(){
    return objeto;
}
bool Slot::esSlotMutable(){
    return this->esMutable;
}
bool Slot::esSlotParent(){
    return this->esParent;
}