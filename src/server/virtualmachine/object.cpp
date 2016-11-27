#include "object.h"
#include "lobby.h"
//(Objeto,isMutable,isParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<Object name, slot>
typedef std::map<std::string, slot_t> slot_map;


/*Objeto generico de Self*/
Object::Object(){
    representation = "";
    myLobby = nullptr;
    objectName = "Object null";
}


/*Constructor por copia*/
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

/*Obtiene el objet de un slot*/
Object* Object::getSlotName(const std::string& name) const{
  Slot slot = slots.getSlot(name);
  return slot.getReference();
}

Object::~Object(){}

/*Setea el nombre*/
void Object::setName(const std::string newName){
    std::cout << "Object::setName:" << newName << std::endl;
    this->objectName = newName;

    myMorph.setName(newName);
    /*TODO no notifico mas cuando se cambia el nombre, notifico al final de la creacion del objectReference*/
}
/*Devuelve el nombre*/
std::string Object::getName() const {
    return this->objectName;
}

/*Agrega un slot*/
void Object::addSlots(std::string slotName,
                      Object* object,
                      bool isMutable,
                      bool isParentSlot){
    std::cout << "Agrego slot: " << slotName <<" de nombre:"<<object->getName()<< " a " << this->getName() << std::endl; //TODO sacar debug


    slots.addSlot(slotName, object, isMutable, isParentSlot);
    if(slotName != "self"){ //No me interesa tener el slot implicito self en el morph del objectReference
        //std::cout << "Agrega el slot " << slotName << " al morph" << std::endl;
        myMorph.addSlot(slotName, object->getRepresentation());
    }
}

void Object::RemoveSlots(std::string slotName) {
    slots.removeSlot(slotName);
    if(slotName != "self"){ //No me interesa tener el slot implicito self en el morph del objectReference
        std::cout << "Elimina el slot " << slotName << " del morph "  << std::endl;
        myMorph.removeSlot(slotName);
    }
}

/*Devuelve un copia de si mismo*/
Object* Object::clone() const{
  std::cout << "Object::clone" << std::endl;
  return new Object(*this);
}

/*Devuelve su RegisterOfSlots*/
RegisterOfSlots Object::getSlots(){
    return slots;
}

/*Devuelve un RegisterOfSlots solo con parentsSlots*/
RegisterOfSlots Object::getParentsSlots() const{
    return slots.getParentsSlots();
}

/*Buscar el objeto de nombre name en el objeto object*/
Object* Object::searchObject(const std::string& name, Object *object) {
    std::cout << "Busco: " << name <<  " en " << object->getName() << std::endl;
    return slots.searchSlot(name, object);
}

/*Devuelve el resultado*/
Object* Object::getResult(){
  return this;
}

void Object::evaluate(){}

/*Setea su representacion*/
void Object::setRepresentation(const std::string representationString){
  representation = representationString;
}
/*Devuelve su representation*/
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

void Object::moveMorph(const std::string clientName, double newX, double newY){
    myMorph.changePosition(newX, newY);
    notifyClients("mover morph", clientName);
}

//Por defecto devuelve los slots
std::vector<Object*> Object::getReferences(){
  RegisterOfSlots slots = this->getSlots();
  return slots.getObjectsNotParent();
}


int Object::getMorphId(){
    return myMorph.getId();
};

void Object::changeMorphName(std::string& newName){
    myMorph.changeName(newName);
}

/*Serializacion*/

void Object::serialize(json& jserialization){
    std::cout << "Object::serialize: " << objectName << std::endl;
    jserialization["objectName"] = objectName;
    jserialization["representation"] = representation;

    json jRegisterOfSlots;
    slots.serialize(jRegisterOfSlots);
    jserialization["slots"] = jRegisterOfSlots;

    json jMorph;
    myMorph.serialize(jMorph);
    jserialization["myMorph"] = jMorph;

    jserialization["type"] = "object";
}

Object* Object::deserialize(json& jdeserialization, Lobby* lobby){
    std::cout << "Object::deserialize start" << std::endl;
    Object* object = new Object();
    object->objectName = jdeserialization["objectName"];
    object->representation = jdeserialization["representation"];

    json jRegisterOfSlots;
    jRegisterOfSlots = jdeserialization["slots"];
    object->slots.deserialize(jRegisterOfSlots, object, lobby);

    json jMorph;
    jMorph = jdeserialization["myMorph"];
    object->myMorph.deserialize(jMorph);

    object->myLobby = lobby;

    std::cout << "Object::deserialize end" << std::endl;

    return object;
}

Object* Object::searchForId(int objectId){
    std::cout << "Busco " << objectId << " en " << this->getName() << std::endl;
    std::cout << "Busco " << objectId << " mi ID: " << this->getMorphId() << std::endl;
    if(this->getMorphId() == objectId)return this;
    std::vector<Object*> mySlotsObjects = this->slots.getObjectsWhitoutParents(); //Para que no haya ciclos de busqueda
    for(auto itObjectSlot = mySlotsObjects.begin(); itObjectSlot != mySlotsObjects.end(); itObjectSlot++){
        if((*itObjectSlot)->getName() != "self") {
            Object *objectFound = (*itObjectSlot)->searchForId(objectId);
            if (objectFound != nullptr) return objectFound;
        }
    }
    return nullptr;
}