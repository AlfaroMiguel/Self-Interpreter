#include "searcher_object.h"
#include "object.h"
#include <stdexcept>

SearcherObject::SearcherObject(std::string nameString):Object(){
  setName(nameString);
  setRepresentation(nameString);
  expressionSearched =  nullptr;
}

SearcherObject::~SearcherObject(){
}


/*Devuelve un NativeValue del objeto del entorno correspondiente, se supone que
ya lo encontro, en caso contrario devuevlve un error*/
NativeValue SearcherObject::getValue(){
  if (expressionSearched != nullptr){
    return expressionSearched->getValue();
  }
  throw std::runtime_error("SearcherObject::Null not cannot return NativeValue");
}

/*Si encontro el objeto se agrega el slot a ese, caso contrario se lo agrega a si mismo*/
void SearcherObject::addSlots(std::string slotName,Object* slot, bool isMutable, bool isParentSlot){
  std::cout << "SearcherObject::addSlots" << std::endl;
  if(expressionSearched != nullptr){
    expressionSearched->addSlots(slotName,slot,isMutable,isParentSlot);
  }else{
    slots.addSlot(slotName, slot, isMutable, isParentSlot);
  }
}
/*Aca obtiene su slot self que sería su entorno y buscar al objeto con el Nombre
objectName*/
void SearcherObject::evaluate(){
  std::cout << "SearcherObject::evaluate" << std::endl;
  std::string selfStr = "self";
  Object* self = getSlotName(selfStr);
  Object* expression = Object::searchObject(objectName, self);
  if (expression != nullptr){
    expressionSearched = expression;
  }else{
    std::cout << "Object not found:" <<objectName<< std::endl;
  }
}

/*Una vez que encontro el objeto se puede enviar un mensaje al objeto que
encontró*/
NativeValue SearcherObject::ejecute(std::string operation, Object* argument){
  if (expressionSearched != nullptr){
    return expressionSearched->ejecute(operation,argument);
  }else{
    throw std::runtime_error("ObjectNull not cannot ejecute operation");
  }
}

/*Devuelve una copia de si mismo*/
Object* SearcherObject::clone(){
  std::cout << "SearcherObject::clone" << std::endl;
  SearcherObject* newSearcheObject = new SearcherObject(objectName);
  newSearcheObject->setRepresentation(objectName);
  std::string selfStr = "self";
  Object* self = getSlotName(selfStr);
  newSearcheObject->addSlots(selfStr,self,false,true);
  return newSearcheObject;
}

void SearcherObject::serialize(json& jserialization){
  std::cout << "SearcherObject::serialize start: " << objectName << std::endl;
  jserialization["objectName"] = objectName;
  jserialization["representation"] = representation;

  json jRegisterOfSlots;
  slots.serialize(jRegisterOfSlots);
  jserialization["slots"] = jRegisterOfSlots;

  json jMorph;
  myMorph.serialize(jMorph);
  jserialization["myMorph"] = jMorph;

  jserialization["type"] = "searcherObject";

  std::cout << "SearcherObject::serialize end " << objectName << std::endl;

}

//Deserealizacion

Object* SearcherObject::deserialize(json& jdeserialization, Lobby* lobby){
  std::cout << "SearcherObject::deserialize start" << std::endl;
  std::string name = jdeserialization["objectName"];
  SearcherObject* searcherobj = new SearcherObject(name);
  searcherobj->objectName = jdeserialization["objectName"];
  searcherobj->representation = jdeserialization["representation"];

  json jRegisterOfSlots;
  jRegisterOfSlots = jdeserialization["slots"];
  searcherobj->slots.deserialize(jRegisterOfSlots, searcherobj, lobby);

  json jMorph;
  jMorph = jdeserialization["myMorph"];
  searcherobj->myMorph.deserialize(jMorph);

  searcherobj->myLobby = lobby;

  std::cout << "SearcherObject::deserialize end" << std::endl;

  return searcherobj;
}
