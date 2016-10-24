#include "method.h"

Method::Method() : Object() {}

Method::~Method() {}

Object* Suma::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    numero->setValor(numero->getValor() + otroNumero->getValor());
    return numero;
}

Object* Resta::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    numero->setValor(numero->getValor() - otroNumero->getValor());
    return numero;
}

Object* Multiplicacion::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    numero->setValor(numero->getValor() * otroNumero->getValor());
    return numero;
}

Object* Division::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    numero->setValor(numero->getValor() / otroNumero->getValor());
    return numero;
}

Object* Igual::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    bool sonIguales = (numero->getValor() == otroNumero->getValor());
    Bool* iguales = new Bool();
    iguales->setValor(sonIguales);
    return iguales;
}

Object* Distinto::ejecutar(std::vector<Object*>& argumentos){
    Number* numero = (Number*)receiver;
    Number* otroNumero = (Number*)argumentos[0];
    bool sonDistintos = (numero->getValor() != otroNumero->getValor());
    Bool* distintos = new Bool();
    distintos->setValor(sonDistintos);
    return distintos;
}