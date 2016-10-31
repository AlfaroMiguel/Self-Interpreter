#ifndef SUMA_H
#define SUMA_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Suma : public Method{
    Object* receiver;
public:
    Suma(Object* receiver);
    ~Suma();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
