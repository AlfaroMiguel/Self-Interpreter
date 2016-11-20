#include "register_of_slots.h"
#include "object.h"

RegisterOfSlots::RegisterOfSlots(){}

RegisterOfSlots::~RegisterOfSlots(){
    slotMap.clear();
}

/*Agrega un slot*/
void RegisterOfSlots::addSlot(std::string slotName, Object *object, bool isMutable, bool isParent){
    Slot newSlot(object, isMutable, isParent);
    if(slotMap.count(slotName) == 1){
      removeSlot(slotName);
    }
    slotMap.insert(make_pair(slotName, newSlot));
}

/*Devulve un slot del nombre slotName*/
Slot RegisterOfSlots::getSlot(std::string &slotName) {
    auto slotIt = slotMap.find(slotName);
    if (slotIt == slotMap.end()){
        std::string error = "No se encontro el slot";
        throw std::runtime_error(error);
    }
    return slotMap.at(slotName);
}


/*Devuelve los objetos que se encuentran en los slots pero no aquellos que
son parents slots*/
std::vector<Object*> RegisterOfSlots::getObjectsNotParent(){
  std::vector<Object*> objects;
  for(auto it = slotMap.begin(); it != slotMap.end(); it++){
    if (!((it->second).isParentSlot())){
      objects.push_back((it->second).getReference());
    }
  }
  return objects;
}
}
/*Devuelve TODOS los objetos que se encuentra en sus slots*/
std::vector<Object*> RegisterOfSlots::getObjects(){
  std::vector<Object*> objects;
  for(auto it = slotMap.begin(); it != slotMap.end(); it++){
    objects.push_back((it->second).getReference());
  }
  return objects;
}


/*Remueve un slot con cierto nombre*/
void RegisterOfSlots::removeSlot(std::string &slotName){
    slotMap.erase(slotName);
}

/*Crea un RegisterOfSlots, inserta los parentsSlot y lo devuelve*/
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

/*Busca el slot de nombre slotName en el objeto Object, sino no lo encuentra
en object busca en los parentsSlots de object*/
Object* RegisterOfSlots::searchSlot(std::string &slotName, Object *object){
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
