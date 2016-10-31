#ifndef MULTIPLICACION_H
#define MULTIPLICACION_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Multiplicacion : public Method{
    Object* receiver;
public:
    Multiplicacion(Object* receiver);
    ~Multiplicacion();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
