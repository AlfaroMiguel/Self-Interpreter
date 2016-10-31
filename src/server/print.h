#ifndef PRINT_H
#define PRINT_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Print : public Method{
    Object* receiver;
public:
    Print(Object* receiver);
    ~Print();
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
