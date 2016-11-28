#ifndef SEARCHER_OBJECT_H
#define SEARCHER_OBJECT_H

#include "object.h"

class SearcherObject:public Object{
  Object* expressionSearched;
public:
    //Metodo para serializar un SearcherObject
    void serialize(json& jserialization);

    //Metodo estatico para la deserealizacion de un SearcherObject
    static Object* deserialize(json& jdeserialization, Lobby* lobby);


    /*Este objeto tiene la responsabilidad de buscar el objeto con el nombre
    seteado dado el contexto en el que se encuentra*/
    SearcherObject(std::string nameString);

    ~SearcherObject();

    /*Si encontro el objeto se agrega el slot a ese, caso contrario se lo agrega a si mismo*/
    void addSlots(std::string slotName,Object* slot, bool isMutable, bool isParentSlot);

    /*Devuelve un NativeValue del objeto del entorno correspondiente, se supone que
    ya lo encontro, en caso contrario devuevlve un error*/
    NativeValue getValue();

    /*Una vez que encontro el objeto se puede enviar un mensaje al objeto que
    encontró*/
    NativeValue ejecute(std::string operation, Object* expression);

    /*Aca obtiene su slot self que sería su entorno y buscar al objeto con el Nombre
    objectName*/
    void evaluate();

    /*Devuelve una copia de si mismo*/
    Object* clone();
    virtual void serialize(json& jserialization);
    static Object* deserialize(json& jdeserialization, Lobby* lobby);
};

#endif
