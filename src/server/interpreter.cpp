#include "interpreter.h"

using std::string;

Interpreter::Interpreter(){}

void Interpreter::crearObjetoNoMutable(string id , float value){
  std::cerr<<"Crear Objeto no mutable"<<std::endl;
  std::cerr<<"Id:"<<id<<std::endl;
  std::cerr<<"value:"<<value<<std::endl;
  myMap.insert(std::pair<string,float>(id,value));
}
void Interpreter::crearObjetoMutable(string id,float value){
  std::cerr<<"Crear Objeto mutable"<<std::endl;
  std::cerr<<"Id:"<<id<<std::endl;
  std::cerr<<"value:"<<value<<std::endl;
  myMap.insert(std::pair<string,float>(id,value));
}

void Interpreter::setObjeto(string id,float value){
  std::cerr<<"Set Objeto"<<std::endl;
  std::cerr<<"Id:"<<id<<std::endl;
  std::cerr<<"value:"<<value<<std::endl;
}
void Interpreter::crearObjeto(){
}

Interpreter::~Interpreter(){}
