#ifndef SELFTP_SLOT_H
#define SELFTP_SLOT_H

class Object;

class Slot{
    Object* objectReference;
    bool isMutable;
    bool isParent;

public:
    Slot(Object* object, bool isMutable, bool isParent);
    ~Slot();
    Object* getReference();
    bool isMutableSlot();
    bool isParentSlot();
};

#endif
