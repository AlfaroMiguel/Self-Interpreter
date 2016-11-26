#include "register_of_slots.h"
#include "object.h"

RegisterOfSlots::RegisterOfSlots(){}

RegisterOfSlots::~RegisterOfSlots(){
    slotMap.clear();
}

void RegisterOfSlots::addSlot(const std::string& slotName, Object *object, bool isMutable, bool isParent){
    Slot newSlot(object, isMutable, isParent);
    if(slotMap.count(slotName) == 1){
      removeSlot(slotName);
    }
    slotMap.insert(make_pair(slotName, newSlot));
}

Slot RegisterOfSlots::getSlot(const std::string& slotName) {
    auto slotIt = slotMap.find(slotName);
    if (slotIt == slotMap.end()){
        std::string error = "No se encontro el slot";
        throw std::runtime_error(error);
    }
    return slotMap.at(slotName);
}

std::vector<Object*> RegisterOfSlots::getObjectsNotParent(){
  std::vector<Object*> objects;
  for(auto it = slotMap.begin(); it != slotMap.end(); it++){
    if (!((it->second).isParentSlot())){
      objects.push_back((it->second).getReference());
    }
  }
  return objects;
}

std::vector<Object*> RegisterOfSlots::getObjects(){
  std::vector<Object*> objects;
  for(auto it = slotMap.begin(); it != slotMap.end(); it++){
    objects.push_back((it->second).getReference());
  }
  return objects;
}

std::vector<Object*> RegisterOfSlots::getObjectsWhitoutParents(){
    std::vector<Object*> objects;
    for(auto it = slotMap.begin(); it != slotMap.end(); it++){
        if(it->first != "self" && !it->second.isParentSlot())
            objects.push_back((it->second).getReference());
    }
    return objects;
}

void RegisterOfSlots::removeSlot(const std::string &slotName){
    slotMap.erase(slotName);
}

RegisterOfSlots RegisterOfSlots::getParentsSlots(){
    RegisterOfSlots registerOfParentsSlots;
    for(auto iter = slotMap.begin(); iter != slotMap.end(); ++iter){
        Slot slot  = iter->second;
        if(slot.isParentSlot()){
            registerOfParentsSlots.addSlot(iter->first,
                                           slot.getReference(),
                                           slot.isMutableSlot(),
                                           slot.isParentSlot());
        }
    }
    return registerOfParentsSlots;
}

Object* RegisterOfSlots::searchSlot(const  std::string &slotName, Object *object){
    if (slotName == object->getName()){ //Si es el object lo devuelvo
        return object;
    }
    RegisterOfSlots slotsDeObject = object->getSlots();
    auto slots_it = slotsDeObject.slotMap.find(slotName); //Sino busco en sus slots
    if(slots_it == slotsDeObject.slotMap.end()){
        RegisterOfSlots parentsSlots = object->getParentsSlots();
        std::vector<Object*> parentsSlotsFounded;
        for(auto iter = parentsSlots.slotMap.begin(); iter != parentsSlots.slotMap.end(); ++iter){
            Object* temporalObject = (iter->second).getReference();
            std::cout << "temporalObject name:" <<temporalObject->getName()<< std::endl;
            Object* parent = searchSlot(slotName, temporalObject);
            parentsSlotsFounded.push_back(parent);
        }
        if(parentsSlotsFounded.size() == 0){
            throw std::runtime_error("No se encontro el object en el lookup");
        }
        if(parentsSlotsFounded.size() > 1){
            throw std::runtime_error("El object se encontro en mas de un parent");
        }
        return parentsSlotsFounded[0];

    }else{
        return (slots_it->second).getReference();
    }
}
