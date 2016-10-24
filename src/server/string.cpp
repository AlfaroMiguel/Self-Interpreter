#include "string.h"

String::String() : Object(){
    Print* printSlot = new Print(this);
    this->AddSlots("print", printSlot, false, false);
}

String::~String(){}

void String::setValor(std::string nuevoValor){
    this->valor = nuevoValor;
}

std::string String::getValor(){
    return this->valor;
}

std::string String::obtenerRepresentacion(){
    return this->getValor();
}

Object* String::print(){
    std::cout << valor << std::endl;
    return this;
}