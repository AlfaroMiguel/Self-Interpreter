#include "number.h"
#include <functional>

Number::Number() : Object(){
    esMutable = true;
    Print* printSlot = new Print(this);
    this->AddSlots("print", printSlot, false, false);
    Suma* sumaSlot = new Suma(this);
    this->AddSlots("+", sumaSlot, false, false);
}

Number::~Number(){}


std::string Number::obtenerRepresentacion(){
    return std::to_string(this->valor);
}

void Number::setValor(float nuevoValor){
    this->valor = nuevoValor;
}

float Number::getValor(){
    return this->valor;
}