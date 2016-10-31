#include "resta.h"
#include "object.h"
#include "number.h"

Resta::Resta(Object* receiver):Method(), receiver(receiver){}

Resta::~Resta(){}
Object* Resta::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  numero->setValor(numero->getValor() - otroNumero->getValor());
  return numero;
}
