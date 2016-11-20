#include "searcher_object.h"
#include "object.h"
#include <stdexcept>

SearcherObject::SearcherObject(std::string nameString):Object(){
  std::cout << "new SearcherObject" << std::endl;
  setName(nameString);
  setRepresentation(nameString);
  expressionSearched =  nullptr;
}

SearcherObject::~SearcherObject(){
}



NativeValue SearcherObject::getValue(){
  if (expressionSearched != nullptr){
    return expressionSearched->getValue();
  }
  throw std::runtime_error("SearcherObject::Null not cannot return NativeValue");
}


void SearcherObject::addSlots(std::string slotName,Object* slot, bool isMutable, bool isParentSlot){
  std::cout << "SearcherObject::addSlots" << std::endl;
  if(expressionSearched != nullptr){
    expressionSearched->addSlots(slotName,slot,isMutable,isParentSlot);
  }else{
    slots.addSlot(slotName, slot, isMutable, isParentSlot);
  }
}

void SearcherObject::evaluate(){
  std::cout << "SearcherObject::evaluate" << std::endl;
  Object* self = getSlotName("self");
  Object* expression = Object::searchObject(objectName, self);
  if (expression != nullptr){
    expressionSearched = expression;
  }else{
    std::cout << "Object not found:" <<objectName<< std::endl;
  }
}

NativeValue SearcherObject::ejecute(std::string operation, Object* argument){
  if (expressionSearched != nullptr){
    return expressionSearched->ejecute(operation,argument);
  }else{
    throw std::runtime_error("ObjectNull not cannot ejecute operation");
  }
}

Object* SearcherObject::clone(){
  std::cout << "SearcherObject::clone" << std::endl;
  SearcherObject* newSearcheObject = new SearcherObject(objectName);
  newSearcheObject->setRepresentation(objectName);
  Object* self = getSlotName("self");
  newSearcheObject->addSlots("self",self,false,true);
  return newSearcheObject;
}
