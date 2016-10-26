#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <iostream> //cout
#include <map>
#include <string>


class Interpreter{
private:
  std::map<std::string,float> myMap;
public:
  Interpreter();
  void crearObjetoNoMutable(std::string id, float value);
  void crearObjetoMutable(std::string id, float value);
  void setObjeto(std::string id,float value);
  void addSlots(std::string id,float value);
  void crearObjeto();
  ~Interpreter();

};

#endif
