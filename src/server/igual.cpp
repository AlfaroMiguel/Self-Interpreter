#include "igual.h"
#include "object.h"
#include "number.h"

Igual::Igual(Object* receiver):Method(), receiver(receiver){}

Igual::~Igual(){}

Object* Igual::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  bool sonIguales = (numero->getValor() == otroNumero->getValor());
  Bool* iguales = new Bool();
  iguales->setValor(sonIguales);
  return iguales;
}
