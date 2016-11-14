#ifndef MAPADESLOTS_H
#define MAPADESLOTS_H

#include "slot.h"
#include <iostream>
#include <map>
#include <vector>

class Object;

class RegistroDeSlots{
    std::map<std::string,Slot> slotMap;
public:
    RegistroDeSlots();
    ~RegistroDeSlots();
    void agregarSlot(std::string nombreSlot,Object* objeto, bool esMutable, bool esParent);
    Slot obtenerSlot(std::string& nombreSlot);
    void removerSlot(std::string& nombreSlot);
    RegistroDeSlots obtenerParentsSlots();
    Object* buscarSlot(std::string& nombre, Object* objeto);
    std::vector<Object*> getObjects();
};

#endif
