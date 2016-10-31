#include "distinto.h"
#include "object.h"
#include "number.h"

Distinto::Distinto(Object* receiver):Method(), receiver(receiver){}

Distinto::~Distinto(){}
Object* Distinto::ejecutar(std::vector<Object*>& argumentos){
  Number* numero = (Number*)receiver;
  Number* otroNumero = (Number*)argumentos[0];
  bool sonDistintos = (numero->getValor() != otroNumero->getValor());
  Bool* distintos = new Bool();
  distintos->setValor(sonDistintos);
  return distintos;
}
