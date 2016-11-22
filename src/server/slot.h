#ifndef SELFTP_SLOT_H
#define SELFTP_SLOT_H

class Object;
/*Encapsula la informacion de un slot de self
 * Contiene la referencia al puntero del objeto
 * Y dos valores booleanos que indican si son mutables o parent slot*/
class Slot{
    Object* objectReference;
    bool isMutable;
    bool isParent;

public:
    /*Constructor recibe la refernecia al objeto, si es mutable y parent*/
    Slot(Object* object, bool isMutable, bool isParent);
    /*Destructor de la clase Slot*/
    ~Slot();
    /*Devuelve la referencia al objeto que contiene*/
    Object* getReference();
    /*Devuelve si es mutable*/
    bool isMutableSlot();
    /*Devuelve si es parent slot*/
    bool isParentSlot();
};

#endif
