#include "object.h"

//(Objeto,isMutable,isParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<Object name, slot>
typedef std::map<std::string, slot_t> slot_map;

Object::Object(){
    representation = "";
    myLobby = nullptr;
    objectName = "Object null";
}

Object::Object(const Object &otherObject) {
    this->objectName = otherObject.objectName;
    this->slots = otherObject.slots;
    this->representation = otherObject.representation;
    this->myLobby = otherObject.myLobby;
    this->myMorph = otherObject.myMorph;
}




//TODO
NativeValue Object::getValue(){
  NativeValue value;
  return value;
}

//TODO
NativeValue Object::ejecute(std::string operationStr, Object* argumentPtr){
  std::cout << "object::ejecute" << std::endl;
  NativeValue value;
  return value;
}

Object* Object::getSlotName(std::string name){
  Slot slot = slots.getSlot(name);
  return slot.getReference();
}

Object::~Object(){}

void Object::setName(const std::string newName){
    std::cout << "Object::setName:" << newName << std::endl;
    this->objectName = newName;

    myMorph.setName(newName);
    //if(myLobby != nullptr)this->notifyClients("crear");
    /*TODO no notifico mas cuando se cambia el nombre, notifico al final de la creacion del objectReference*/
}

std::string Object::getName() {
    return this->objectName;
}

void Object::addSlots(std::string slotName,
                      Object* object,
                      bool isMutable,
                      bool isParentSlot){
    std::cout << "Agrego slot: " << slotName <<" de nombre:"<<object->getName()<< " a " << this->getName() << std::endl; //TODO sacar debug


    slots.addSlot(slotName, object, isMutable, isParentSlot);
    if(slotName != "self"){ //No me interesa tener el slot implicito self en el morph del objectReference
        std::cout << "Agrega el slot " << slotName << " al morph" << std::endl;
        myMorph.addSlot(slotName, object->getRepresentation());
    }
}

void Object::RemoveSlots(std::string slotName) {
    slots.removeSlot(slotName);
}

Object* Object::clone(){
  std::cout << "Object::clone" << std::endl;
  return new Object(*this);
}

RegisterOfSlots Object::getSlots(){
    return slots;
}

RegisterOfSlots Object::getParentsSlots(){
    return slots.getParentsSlots();
}

Object* Object::searchObject(std::string name, Object *object) {
    std::cout << "Busco: " << name <<  " en " << object->getName() << std::endl;
    return slots.searchSlot(name, object);
}

Object* Object::getResult(){
  return this;
}

void Object::evaluate(){}

void Object::setRepresentation(std::string representationString){
  representation = representationString;
}
std::string Object::getRepresentation() const {
  return representation;
}

//TODO "Arreglar este metodo"
Object* Object::print(const std::vector<Object*>& argumnets){
  return this;
}


/*Metodos de los morphs*/

void Object::setLobby(Lobby *lobby) {
    std::cout << "Soy el objectReference " << objectName << " y estoy adentro del lobby " << lobby->getLobbyName() << std::endl;
    myLobby = lobby;
}

void Object::notifyClients(std::string eventName, std::string clientName){
    if(myLobby != nullptr) {
        std::cout << "Notifico clientes" << std::endl;
        myLobby->notifyClients(eventName, myMorph, clientName);

    }
}

void Object::moveMorph(std::string clientName, double newX, double newY){
    myMorph.changePosition(newX, newY);
    notifyClients("mover morph", clientName);
}

int Object::getMorphId(){
    return myMorph.getId();
};
