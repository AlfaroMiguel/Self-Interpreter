#ifndef SELFTP_METHOD_H
#define SELFTP_METHOD_H

#include "number.h"
#include "object.h"

class Method : public Object{
private:
public:
    Method();
    ~Method();
    virtual Object* ejecutar(std::vector<Object*>& argumentos) = 0;
};

#endif
