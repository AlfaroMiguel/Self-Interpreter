#include "registrodeslots.h"
#include "object.h"

RegistroDeSlots::RegistroDeSlots(){}

RegistroDeSlots::~RegistroDeSlots(){
    slotMap.clear();
}

void RegistroDeSlots::agregarSlot(std::string nombreSlot,Object* objeto, bool esMutable, bool esParent){
    Slot slotNuevo(objeto, esMutable, esParent);
    slotMap.insert(make_pair(nombreSlot, slotNuevo));
}

Slot RegistroDeSlots::obtenerSlot(std::string& nombreSlot) {
    auto slotIt = slotMap.find(nombreSlot);
    if (slotIt == slotMap.end()){
        std::string error = "No se encontro el slot";
        throw std::runtime_error(error);
    }
    return slotMap.at(nombreSlot);
}


std::vector<Object*> RegistroDeSlots::getObjects(){
  std::vector<Object*> objects;
  for(auto it = slotMap.begin(); it != slotMap.end(); it++){
    objects.push_back((it->second).obtenerReferencia());
  }
  return objects;
}

void RegistroDeSlots::removerSlot(std::string& nombreSlot){
    slotMap.erase(nombreSlot);
}

RegistroDeSlots RegistroDeSlots::obtenerParentsSlots(){
    RegistroDeSlots registroDeParents;
    for(auto iter = slotMap.begin(); iter != slotMap.end(); ++iter){
        Slot slot  = iter->second;
        if(slot.esSlotParent()){
            std::cout <<"slot"<< slot.obtenerReferencia()->getName() << std::endl;
            registroDeParents.agregarSlot(iter->first, slot.obtenerReferencia(), slot.esSlotMutable(), slot.esSlotParent());
        }
    }
    return registroDeParents;
}

Object* RegistroDeSlots::buscarSlot(std::string& nombre, Object* objeto){
    std::cout << "RegistrosDeSlots::buscarSlot" <<nombre<<":"<<objeto->getName()<< std::endl;
    if (nombre == objeto->getName()){ //Si es el objeto lo devuelvo
        return objeto;
    }
    RegistroDeSlots slotsDeObject = objeto->getSlots();
    auto slots_it = slotsDeObject.slotMap.find(nombre); //Sino busco en sus slots
    if(slots_it == slotsDeObject.slotMap.end()){
        std::cout << "slots_it == slotsDeObject.slotMap.end()" << std::endl;
        RegistroDeSlots parentSlots = obtenerParentsSlots();
        std::vector<Object*> parentsEncontrados;
        std::cout << "cantidad de parentSlots encontrados" <<parentsEncontrados.size()<< std::endl;
        for(auto iter = parentSlots.slotMap.begin(); iter != parentSlots.slotMap.end(); ++iter){
            Object* objetoTemporal = (iter->second).obtenerReferencia();
            std::cout << "objetoTemporal" <<objetoTemporal->getName()<< std::endl;
            Object* parent = buscarSlot(nombre, objetoTemporal);
            parentsEncontrados.push_back(parent);
        }
        if(parentsEncontrados.size() == 0){
            throw std::runtime_error("No se encontro el objeto en el lookup");
        }
        if(parentsEncontrados.size() > 1){
            throw std::runtime_error("El objeto se encontro en mas de un parent");
        }
        return parentsEncontrados[0];

    }else{
        return (slots_it->second).obtenerReferencia();
    }
}
