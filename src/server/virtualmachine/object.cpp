#include "object.h"
#include "lobby.h"
//(Objeto,isMutable,isParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<Object name, slot>
typedef std::map<std::string, slot_t> slot_map;


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

NativeValue Object::getValue(){
  NativeValue value;
  return value;
}

NativeValue Object::ejecute(std::string operationStr, Object* argumentPtr){
  NativeValue value;
  return value;
}

Object* Object::getSlotName(const std::string& name) const{
  Slot slot = slots.getSlot(name);
  return slot.getReference();
}

Object::~Object(){}

/*Setea el nombre*/
void Object::setName(const std::string newName){
    this->objectName = newName;
    myMorph.setName(newName);
    /*No notifico mas cuando se cambia el nombre, notifico al final de la creacion del objectReference*/
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

    object->myMorph.setUnionName(slotName); //TEST LINEA

    slots.addSlot(slotName, object, isMutable, isParentSlot);
    if(slotName != "self"){ //No me interesa tener el slot implicito self en el morph del objectReference
        myMorph.addSlot(slotName, object->getRepresentation());
    }
}

void Object::RemoveSlots(std::string slotName) {
    slots.removeSlot(slotName);
    if(slotName != "self"){ //No me interesa tener el slot implicito self en el morph del objectReference
        myMorph.removeSlot(slotName);
    }
}

Object* Object::clone() const{
  return new Object(*this);
}

RegisterOfSlots Object::getSlots(){
    return slots;
}

RegisterOfSlots Object::getParentsSlots() const{
    return slots.getParentsSlots();
}

Object* Object::searchObject(const std::string& name, Object *object) {
    return slots.searchSlot(name, object);
}

Object* Object::getResult(){
  return this;
}

void Object::evaluate(){}

void Object::setRepresentation(const std::string representationString){
  representation = representationString;
}
std::string Object::getRepresentation() const {
  return representation;
}




/*Metodos de los morphs*/

void Object::setLobby(Lobby *lobby) {
    myLobby = lobby;
}

void Object::notifyClients(std::string eventName, std::string clientName){
    if(myLobby != nullptr) {
        myLobby->notifyClients(eventName, myMorph, clientName);

    }
}

void Object::moveMorph(const std::string clientName, double newX, double newY){
    myMorph.changePosition(newX, newY);
    notifyClients("mover morph", clientName);
}

std::vector<Object*> Object::getReferences(){
  RegisterOfSlots slots = this->getSlots();
  return slots.getObjectsNotParent();
}
std::vector<Object*> Object::getAtributs(){
  std::vector<Object*> v;
  return v;
}


int Object::getMorphId(){
    return myMorph.getId();
};

void Object::changeMorphName(std::string& newName){
    myMorph.changeName(newName);
}

void Object::changeObjectName(const std::string& newName) {
    this->objectName = newName;
    this->changeMorphName((std::string&)newName);
}

/*Serializacion*/

void Object::serialize(json& jserialization){
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
    return object;
}

Object* Object::searchForId(int objectId){
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
