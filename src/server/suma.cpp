#include "suma.h"
#include "object.h"
#include "number.h"

Suma::Suma(Object* receiver):Method(), receiver(receiver){}

Suma::~Suma(){}

Object* Suma::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  numero->setValor(numero->getValor() + otroNumero->getValor());
  return numero;
}
