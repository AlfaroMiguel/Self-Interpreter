#include "object.h"
//#include "method.h"

#define POS_OBJETO 0
#define POS_ES_MUTABLE 1
#define POS_ES_PARENT_SLOT 2

//(Objeto,esMutable,esParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<NombreObjeto, slot>
typedef std::map<std::string, slot_t> slot_map;


Object::Object(){
    this->nombre = "Null Object";
}

Object::Object(const Object &otro) {
    this->nombre = otro.nombre;
    //this->slots = otro.slots;
    //this->codigo = otro.codigo;
}

Object::~Object(){}

void Object::setName(const std::string nuevoNombre) {
    this->nombre = nuevoNombre;
}

std::string Object::getName() {
    return this->nombre;
}

void Object::addSlots(std::string nameSlot,
                      Object* object,
                      bool esMutable,
                      bool esParentSlot){
    //std::cout << "Agrego slot: " << nombreSlot << " a " << this->nombre << std::endl;
    //slots.agregarSlot(nombreSlot, object, esMutable, esParentSlot);
}

void Object::removeSlots(std::string nameSlot) {
    //slots.removerSlot(nombreSlot);
}

// void Object::setCodigo(const std::string nuevoCodigo){
//     this->codigo = nuevoCodigo;
// }
//
// std::string Object::obtenerCodigo() const {
//     return this->codigo;
// }

Object* Object::clone() {
    return new Object(*this);
}
//
// RegistroDeSlots Object::getSlots(){
//     return slots;
// }
//
// RegistroDeSlots Object::getParentsSlots(){
//     return slots.obtenerParentsSlots();
// }

// Object* Object::buscarObject(std::string nombre, Object *object) {
//     //std::cout << "Busco: " << nombre <<  " en " << object->obtenerNombre() << std::endl;
//     return slots.buscarSlot(nombre, object);
// }


// Object* Object::recvMessage(std::string receiverName,
//                     std::string keyWordMensaje,
//                     std::vector<Object*> argumentos){
//     Object* receiverObject;
//     receiverObject = buscarObject(receiverName, this);
//     Object* mensajeObject = buscarObject(keyWordMensaje, receiverObject);
//     ((Method*)mensajeObject)->ejecutar(argumentos);
//     /*Si no se puede ejecutar lo de arriba es porque no es un operador
//      * +, -, *, /, ==, !=, print
//      * Por lo que seria un MethodObject con codigo asociado
//      * ese codigo se debe pasar al parser y "decodificarlo"*/
//      return this;
// }

/*arreglar este método*/
// std::string Object::obtenerRepresentacion(){
//   std::string algo = "aa";
//   return algo;
// }

/*arreglar este método*/
// Object* Object::print(const std::vector<Object*>& argumentos){
//   return this;
// }
