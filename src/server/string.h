#ifndef SELFTP_STRING_H
#define SELFTP_STRING_H

#include "object.h"
#include "method.h"

class String : public Object{
    std::string valor;
public:
    String();
    ~String();
    void setValor(std::string nuevoValor);
    std::string getValor();
    std::string obtenerRepresentacion();
    Object* print();
};

#endif
