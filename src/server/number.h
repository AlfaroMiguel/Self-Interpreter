#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"
#include "bool.h"
#include "method.h"

class Number : public Object{
private:
    float valor;
    bool esMutable;
public:
    Number();
    ~Number();

    void setValor(float nuevoValor);
    float getValor();
    std::string obtenerRepresentacion();
};

#endif