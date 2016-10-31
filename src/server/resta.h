#ifndef RESTA_H
#define RESTA_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Resta : public Method{
    Object* receiver;
public:
    Resta(Object* receiver);
    ~Resta();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
