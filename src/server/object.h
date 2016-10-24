#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <functional>


class Object{

public:
    //(Objeto,esMutable,esParent)
    typedef std::tuple<Object*, bool, bool> slot_t;
    //<NombreObjeto, slot>
    typedef std::map<std::string, slot_t> slot_map;

protected:
    std::string nombre;
    slot_map slots;
    std::string codigo;

    slot_map obtenerParentsSlots() const;

    Object* buscarObject(std::string nombre, Object* object);

public:
    Object();
    Object(const Object& otroObject);
    ~Object();


    void setNombre(const std::string nuevoNombre);
    std::string obtenerNombre();

    void AddSlots(std::string nombreSlot, Object* object, bool esMutable, bool esParentSlot);
    void RemoveSlots(std::string nombreSlot);

    void setCodigo(const std::string nuevoCodigo);
    std::string obtenerCodigo() const;

    Object* recvMessage(std::string receiverObject,
                        std::string keyWordMensaje,
                        std::vector<Object*> argumentos);

    Object* clone();
    virtual std::string obtenerRepresentacion(){};
    virtual Object* print(const std::vector<Object*>& argumentos){};

    //Object* collect(); Esto va en el Lobby
};

#endif
