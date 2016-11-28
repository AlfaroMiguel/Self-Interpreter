#ifndef JSON_LIB
#define JSON_LIB
#include "../../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include "register_of_slots.h"
#include "nativevalue.h"

#include "morph.h"
class Lobby;

class Object{
protected:
    std::string objectName;
    RegisterOfSlots slots;
    std::string representation;
    Morph myMorph;
    Lobby* myLobby;
    friend class Interpreter;
public:

    /*Objeto generico de Self*/
    Object();

    Object(const Object& otherObject);
    virtual ~Object();


    /*Devuelve el object con el nombre que se le dio*/
    Object* getSlotName(const std::string& name) const;


    /*Devuelve un RegisterOfSlots solo con parentsSlots*/
    RegisterOfSlots getParentsSlots() const;

    /*Buscar el objeto de nombre name en el objeto object*/
    Object* searchObject(const std::string& name, Object *object);

    virtual void setReceiver(Object* receiverPtr){
      std::cout << "Object::setReceiver:" << std::endl;
    }
    virtual void setOperator(std::string operatorString){
      std::cout << "Object::setOperator:" << std::endl;
    }
    virtual void setArgument(Object* argumentPtr){
      std::cout << "Object::setArgument:" << std::endl;
    }

    /*Devuelve el resultado luego de haber ejecutado alguna operacion
    sobre el objeto*/
    virtual void setResult(Object* resultPtr){}
    virtual NativeValue getValue();
    virtual Object* getResult();
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);

    /*Dado se le envio un mensaje con un operation y los argumentos correspondiente
    se pide que se evalue mensaje*/
    virtual void evaluate();

    /*Se setea el nombre del objeto*/
    void setName(const std::string newName);

    /*Se obtiene el nombre del objeto*/
    std::string getName() const;


    //Por defecto devuelve los slots que contiene
    virtual std::vector<Object*> getReferences();


    /*Devuelve en un vector todos los atributos a los cuales contiene, sí y solo
    sí solo viven en él.*/
    virtual std::vector<Object*> getAtributs();

    /*Devuelve su RegisterOfSlots*/
    RegisterOfSlots getSlots();
    /*Se agrega al objeto un slot con el object que se ingresa y slotName, para eso es
    necesario saber si un MubableObjct y si es parentSlot*/
    virtual void addSlots(std::string slotName, Object* object, bool isMutable, bool isParentSlot);
    void RemoveSlots(std::string slotName);

    /*Devuelve un copia de si mismo*/
    virtual Object* clone() const;

    /*Devuelve su representation*/
    virtual std::string getRepresentation() const;

    /*Setea su representacion*/
    virtual void setRepresentation(const std::string representationString);
    virtual Object* print(const std::vector<Object*>& argumnets);



    /*Se setea el lobby del objeto para luego saber a qué Lobby notificar*/
    void setLobby(Lobby* lobby);
    void notifyClients(std::string eventName, std::string clientName = "");
    void moveMorph(const std::string clientName, double newX, double newY);
    int getMorphId();
    void changeMorphName(std::string& newName);
    Object* searchForId(int objectId);
    void changeObjectName(const std::string& newName);

    /*Serializacion*/
    virtual void serialize(json& jserialization);
    static Object* deserialize(json& jdeserialization, Lobby* lobby);

};

#endif
