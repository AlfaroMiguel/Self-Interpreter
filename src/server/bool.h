#ifndef SELFTP_BOOL_H
#define SELFTP_BOOL_H

#include "object.h"

class Bool : public Object{
    bool valor;
public:
    Bool();
    ~Bool();
    void setValor(bool valor);
    bool getValor();
    Object* print();
};

#endif
