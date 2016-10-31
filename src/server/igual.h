#ifndef IGUAL_H
#define IGUAL_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Igual : public Method{
    Object* receiver;
public:
    Igual(Object* receiver);
    ~Igual();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
