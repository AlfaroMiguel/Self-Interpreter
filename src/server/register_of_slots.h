#ifndef REGISTEROFSLOTS_H
#define REGISTEROFSLOTS_H

#include "slot.h"
#include <iostream>
#include <map>
#include <vector>

class Object;

class RegisterOfSlots{
    std::map<std::string,Slot> slotMap;
public:
    RegisterOfSlots();
    ~RegisterOfSlots();
    void addSlot(std::string slotName, Object *object, bool isMutable, bool isParent);
    Slot getSlot(std::string &slotName);
    void removeSlot(std::string &slotName);
    RegisterOfSlots getParentsSlots();
    Object* searchSlot(std::string &slotName, Object *object);
    std::vector<Object*> getObjects();
    std::vector<Object*> getObjectsNotParent();
};

#endif
