#include "division.h"
#include "object.h"
#include "number.h"

Division::Division(Object* receiver):Method(), receiver(receiver){}

Division::~Division(){}
Object* Division::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  numero->setValor(numero->getValor() / otroNumero->getValor());
  return numero;
}
