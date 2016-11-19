#include "object.h"

#define POS_OBJETO 0
#define POS_ES_MUTABLE 1
#define POS_ES_PARENT_SLOT 2

//(Objeto,esMutable,esParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<NombreObjeto, slot>
typedef std::map<std::string, slot_t> slot_map;


Object::Object(){
  std::cout << "create___Object____" << std::endl;
    representation = "";
    myLobby = nullptr;
}

Object::Object(const Object &otro) {
    this->nombre = otro.nombre;
    this->slots = otro.slots;
    //this->codigo = otro.codigo;
}


void Object::isObject(){
  std::cout << "Soy un objeto" << std::endl;

}
/*ver que onda*/
NativeValue Object::getValue(){
  NativeValue value;
  return value;
}


/*ver que onda*/
NativeValue Object::ejecute(std::string operationStr, Object* argumentPtr){
  std::cout << "object::ejecute" << std::endl;
  NativeValue value;
  return value;
}

Object* Object::getSlotName(std::string name){
  Slot slot =  slots.obtenerSlot(name);
  return slot.obtenerReferencia();
}

Object::~Object(){}

void Object::setName(const std::string nuevoNombre){
    std::cout << "Object::setName:" << nuevoNombre << std::endl;
    this->nombre = nuevoNombre;

    myMorph.setName(nuevoNombre);
    if(myLobby != nullptr)this->notifyClients("crear");
}

std::string Object::getName() {
    return this->nombre;
}


void Object::addSlots(std::string nombreSlot,
                      Object* object,
                      bool esMutable,
                      bool esParentSlot){
    std::cout << "Agrego slot: " << nombreSlot << " a " << this->getName() << std::endl;

    std::cout << "Nombre: " << nombre << " Representacion: " << object->getRepresentation() << std::endl;

    slots.agregarSlot(nombreSlot, object, esMutable, esParentSlot);
    if(nombreSlot != "self"){
        std::cout << "Agrega el slot " << nombreSlot << " al morph" << std::endl;
        myMorph.addSlot(nombreSlot, object->getRepresentation());
    }

}

void Object::RemoveSlots(std::string nombreSlot) {
    slots.removerSlot(nombreSlot);
}

Object* Object::clone() {
    return new Object(*this);
}

RegistroDeSlots Object::getSlots(){
    return slots;
}

RegistroDeSlots Object::obtenerParentsSlots(){
    return slots.obtenerParentsSlots();
}

Object* Object::buscarObject(std::string nombre, Object* object) {
    std::cout << "Busco: " << nombre <<  " en " << object->getName() << std::endl;
    return slots.buscarSlot(nombre, object);
}


Object* Object::getResult(){
  return this;
}

void Object::evaluate(){}


/*arreglar este método*/
void Object::setRepresentation(std::string representationStr){
  representation = representationStr;
}
std::string Object::getRepresentation() const {
  return representation;
}

/*arreglar este método*/
Object* Object::print(const std::vector<Object*>& argumentos){
  return this;
}

void Object::setLobby(Lobby *lobby) {
    std::cout << "Soy el objeto " << nombre << " y estoy adentro del lobby " << lobby->getLobbyName() << std::endl;
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