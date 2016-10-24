#ifndef SELFTP_METHOD_H
#define SELFTP_METHOD_H

#include "number.h"

class Method : public Object{
private:
public:
    Method();
    ~Method();
    virtual Object* ejecutar(std::vector<Object*>& argumentos){};
};

class Print : public Method{
    Object* receiver;
public:
    Print(Object* receiver) : Method(), receiver(receiver){};
    ~Print(){};
    Object* ejecutar(std::vector<Object*>& argumentos){
        std::cout << receiver->obtenerRepresentacion();
        return receiver;
    }
};

class Suma : public Method{
    Object* receiver;
public:
    Suma(Object* receiver) : Method(), receiver(receiver){};
    ~Suma(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

class Resta : public Method{
    Object* receiver;
public:
    Resta(Object* receiver) : Method(), receiver(receiver){};
    ~Resta(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

class Multiplicacion : public Method{
    Object* receiver;
public:
    Multiplicacion(Object* receiver) : Method(), receiver(receiver){};
    ~Multiplicacion(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

class Division : public Method{
    Object* receiver;
public:
    Division(Object* receiver) : Method(), receiver(receiver){};
    ~Division(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

class Igual : public Method{
    Object* receiver;
public:
    Igual(Object* receiver) : Method(), receiver(receiver){};
    ~Igual(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

class Distinto : public Method{
    Object* receiver;
public:
    Distinto(Object* receiver) : Method(), receiver(receiver){};
    ~Distinto(){};
    Object* ejecutar(std::vector<Object*>& argumentos);
};

#endif
