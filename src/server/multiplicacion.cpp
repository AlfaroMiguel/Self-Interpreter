#include "multiplicacion.h"
#include "object.h"
#include "number.h"

Multiplicacion::Multiplicacion(Object* receiver):Method(), receiver(receiver){}

Multiplicacion::~Multiplicacion(){}

Object* Multiplicacion::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  numero->setValor(numero->getValor() * otroNumero->getValor());
  return numero;
}
