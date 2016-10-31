#ifndef DIVISION_H
#define DIVISION_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Division : public Method{
    Object* receiver;
public:
    Division(Object* receiver);
    ~Division();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
