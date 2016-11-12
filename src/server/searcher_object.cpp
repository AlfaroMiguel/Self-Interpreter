#include "searcher_object.h"
#include "object.h"
#include <stdexcept>

SearcherObject::SearcherObject(std::string nameString):Object(){
  setName(nameString);
}

SearcherObject::~SearcherObject(){
}



NativeValue SearcherObject::getValue(){
  if (expressionSearched != nullptr){
    return expressionSearched->getValue();
  }
  throw std::runtime_error("SearcherObject::Null not cannot return NativeValue");
}


void SearcherObject::addSlots(std::string id,Object* slot, bool algo, bool otro){
  if(expressionSearched != nullptr){
    expressionSearched->addSlots(id,slot,algo,otro);
  }else{
    std::cout << "SearcherObject No se puede addSlots a un objet Null" << std::endl;
  }
}

void SearcherObject::evaluate(){
  Object* self = getSlotName("self");
  Object* expression = Object::buscarObject(nombre,self);
  if (expression != nullptr){
    expressionSearched = expression;
  }else{
    std::cout << "Object not found:" <<nombre<< std::endl;
  }
}

NativeValue SearcherObject::ejecute(std::string operation, Object* argument){
  if (expressionSearched != nullptr){
    return expressionSearched->ejecute(operation,argument);
  }else{
    throw std::runtime_error("ObjectNull not cannot ejecute operation");
  }
}
