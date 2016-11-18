#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include "registrodeslots.h"
#include "nativevalue.h"

#include "morph.h"
#include "lobby.h"

class Object{
protected:
    std::string nombre;
    RegistroDeSlots slots;
    std::string representation; /*represetancion*/

    Morph myMorph;
    Lobby* myLobby;

public:
    Object();
    Object(const Object& otroObject);
    virtual ~Object();
    Object* getSlotName(std::string name);
    virtual void isObject();
    /*metodos de expression*/
    RegistroDeSlots obtenerParentsSlots();
    Object* buscarObject(std::string nombre, Object* object);
    virtual void setReceiver(Object* receiverPtr){
      std::cout << "Object::setReceiver:" << std::endl;
    }
    virtual void setOperator(std::string operatorString){
      std::cout << "Object::setOperator:" << std::endl;
    }
    virtual void setArgument(Object* argumentPtr){
      std::cout << "Object::setArgument:" << std::endl;
    }
    virtual void setResult(Object* resultPtr){
      std::cout << "Object::setName:"<< std::endl;
    }
    virtual NativeValue getValue();
    virtual Object* getResult();
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);
    virtual void evaluate();

    void setName(const std::string nuevoNombre);
    std::string getName();
    RegistroDeSlots getSlots();
    void addSlots(std::string nombreSlot, Object* object, bool esMutable, bool esParentSlot);
    void RemoveSlots(std::string nombreSlot);


    RegistroDeSlots obtenerSlots();

    Object* clone();
    virtual std::string getRepresentation() const;
    virtual void setRepresentation(std::string representationStr);
    virtual Object* print(const std::vector<Object*>& argumentos);

    //Object* collect(); Esto va en el Lobby

    void setLobby(Lobby* lobby);
    void notifyClients(std::string eventName, std::string clientName = "");
    void moveMorph(std::string clientName, double newX, double newY);
};

#endif
