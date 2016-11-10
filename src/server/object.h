#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
//#include "registrodeslots.h"

class Object{
protected:
    std::string nombre;
    //RegistroDeSlots slots;
    //std::string codigo;
    //RegistroDeSlots obtenerParentsSlots();
    //Object* buscarObject(std::string nombre, Object* object);

public:
    Object();
    Object(const Object& otroObject);
    ~Object();

    void setName(const std::string nuevoNombre);
    std::string getName();

    void addSlots(std::string nombreSlot, Object* object, bool esMutable, bool esParentSlot);
    void removeSlots(std::string nombreSlot);

    //Object* recvMessage(std::string message);

    //RegistroDeSlots obtenerSlots();

    Object* clone();
    // virtual std::string obtenerRepresentacion();
    // virtual Object* print(const std::vector<Object*>& argumentos);

    //Object* collect(); Esto va en el Lobby
};

#endif
