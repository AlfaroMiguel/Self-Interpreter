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
}

Object::Object(const Object &otro) {
    this->nombre = otro.nombre;
    this->slots = otro.slots;
    this->codigo = otro.codigo;
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
    std::cout << "Object::setName:" <<nuevoNombre<< std::endl;
    this->nombre = nuevoNombre;
}

std::string Object::getName() {
    return this->nombre;
}


void Object::addSlots(std::string nombreSlot,
                      Object* object,
                      bool esMutable,
                      bool esParentSlot){
    //std::cout << "Agrego slot: " << nombreSlot << " a " << this->nombre << std::endl;
    slots.agregarSlot(nombreSlot, object, esMutable, esParentSlot);
}

void Object::RemoveSlots(std::string nombreSlot) {
    slots.removerSlot(nombreSlot);
}

void Object::setCodigo(const std::string nuevoCodigo){
    this->codigo = nuevoCodigo;
}

std::string Object::obtenerCodigo() const {
    return this->codigo;
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
    //std::cout << "Busco: " << nombre <<  " en " << object->obtenerNombre() << std::endl;
    return slots.buscarSlot(nombre, object);
}




Object* Object::getResult(){
  return this;
}

void Object::evaluate(){}


/*arreglar este método*/
std::string Object::obtenerRepresentacion(){
  std::string algo = "aa";
  return algo;
}

/*arreglar este método*/
Object* Object::print(const std::vector<Object*>& argumentos){
  return this;
}
