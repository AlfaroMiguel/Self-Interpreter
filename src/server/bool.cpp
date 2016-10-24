#include "bool.h"

Bool::Bool() : Object(){}

Bool::~Bool() {}

void Bool::setValor(bool valor) {
    this->valor = valor;
}

bool Bool::getValor(){
    return this->valor;
}

Object* Bool::print(){
    std::cout << valor;
}