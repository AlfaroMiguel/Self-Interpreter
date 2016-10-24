#include "object.h"
#include "method.h"

#define POS_OBJETO 0
#define POS_ES_MUTABLE 1
#define POS_ES_PARENT_SLOT 2

//(Objeto,esMutable,esParent)
typedef std::tuple<Object*, bool, bool> slot_t;
//<NombreObjeto, slot>
typedef std::map<std::string, slot_t> slot_map;

Object::Object(){
    this->nombre = "object";
}

Object::Object(const Object &otro) {
    this->nombre = otro.nombre;
    this->slots = otro.slots;
    this->codigo = otro.codigo;
}

Object::~Object(){
    slots.clear();
}

void Object::setNombre(const std::string nuevoNombre) {
    this->nombre = nuevoNombre;
}

std::string Object::obtenerNombre() {
    return this->nombre;
}

void Object::AddSlots(std::string nombreSlot,
                      Object* object,
                      bool esMutable,
                      bool esParentSlot){

    //std::cout << "Agrego slot: " << nombreSlot << " a " << this->nombre << std::endl;

    this->slots.insert(std::make_pair(nombreSlot,
    std::make_tuple(object,esMutable,esParentSlot)));
}

void Object::RemoveSlots(std::string nombreSlot) {
    auto slot_it = slots.find(nombreSlot);
    if(slot_it != slots.end()){
        slots.erase(slot_it);
    }else
        throw std::runtime_error("No se encontro el slot a remover");
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

slot_map Object::obtenerParentsSlots() const{
    slot_map parentSlots;
    for(auto iter = slots.begin(); iter != slots.end(); ++iter){
        if(std::get < POS_ES_PARENT_SLOT > (iter->second)) {
            parentSlots.insert(std::make_pair(iter->first, iter->second));
        }
    }
    return parentSlots;
}

Object* Object::buscarObject(std::string nombre, Object *object) {
    //std::cout << "Busco: " << nombre <<  " en " << object->obtenerNombre() << std::endl;
    if (nombre == object->nombre){ //Si es el objeto lo devuelvo
        return object;
    }
    slot_map slots = object->slots;
    auto slots_it = slots.find(nombre); //Sino busco en sus slots
    if(slots_it == slots.end()){
        slot_map parentSlots = obtenerParentsSlots();
        std::vector<Object*> parentsEncontrados;
        for(auto iter = parentSlots.begin(); iter != parentSlots.end(); ++iter){
            Object* objetoTemporal = (Object*)std::get<0>(iter->second);
            Object* parent;
            parent = buscarObject(nombre, objetoTemporal);
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
        return std::get< POS_OBJETO > (slots_it->second);
    }
}


Object* Object::recvMessage(std::string receiverName,
                    std::string keyWordMensaje,
                    std::vector<Object*> argumentos){
    Object* receiverObject;
    receiverObject = buscarObject(receiverName, this);
    Object* mensajeObject = buscarObject(keyWordMensaje, receiverObject);
    ((Method*)mensajeObject)->ejecutar(argumentos);
    /*Si no se puede ejecutar lo de arriba es porque no es un operador
     * +, -, *, /, ==, !=, print
     * Por lo que seria un MethodObject con codigo asociado
     * ese codigo se debe pasar al parser y "decodificarlo"*/

}