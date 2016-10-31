#include "print.h"
#include "object.h"
#include "number.h"

Print::Print(Object* receiver):Method(), receiver(receiver){}

Print::~Print(){}
Object* Print::ejecutar(std::vector<Object*>& argumentos){
  std::cout << receiver->obtenerRepresentacion();
  return receiver;
}
