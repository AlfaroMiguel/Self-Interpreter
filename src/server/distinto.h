#ifndef DISTINTO_H
#define DISTINTO_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Distinto : public Method{
    Object* receiver;
public:
    Distinto(Object* receiver);
    ~Distinto();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
