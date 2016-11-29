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

NativeValue SearcherObject::getValue(){
  if (expressionSearched != nullptr){
    return expressionSearched->getValue();
  }
  throw std::runtime_error("SearcherObject::Null not cannot return NativeValue");
}

void SearcherObject::addSlots(std::string slotName,Object* slot, bool isMutable, bool isParentSlot){
  if(expressionSearched != nullptr){
    expressionSearched->addSlots(slotName,slot,isMutable,isParentSlot);
  }else{
    slots.addSlot(slotName, slot, isMutable, isParentSlot);
  }
}



void SearcherObject::evaluate(){
  std::string selfStr = "self";
  Object* self = getSlotName(selfStr);
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

Object* SearcherObject::clone() const{
  SearcherObject* newSearcheObject = new SearcherObject(objectName);
  newSearcheObject->setRepresentation(objectName);
  std::string selfStr = "self";
  Object* self = getSlotName(selfStr);
  newSearcheObject->addSlots(selfStr,self,false,true);
  return newSearcheObject;
}


void SearcherObject::serialize(json& jserialization){
    jserialization["objectName"] = objectName;
    jserialization["representation"] = representation;

    json jRegisterOfSlots;
    slots.serialize(jRegisterOfSlots);
    jserialization["slots"] = jRegisterOfSlots;

    json jMorph;
    myMorph.serialize(jMorph);
    jserialization["myMorph"] = jMorph;

    jserialization["type"] = "searcherObject";
}

Object* SearcherObject::deserialize(json& jdeserialization, Lobby* lobby){
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
    return searcherobj;
}
