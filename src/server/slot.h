#ifndef SELFTP_SLOT_H
#define SELFTP_SLOT_H

class Object;

class Slot{
    Object* objeto;
    bool esMutable;
    bool esParent;

public:
    Slot(Object* objeto, bool esMutable, bool esParent);
    ~Slot();
    Object* obtenerReferencia();
    bool esSlotMutable();
    bool esSlotParent();
};

#endif
