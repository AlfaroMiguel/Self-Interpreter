#include "expression.h"
#include "object.h"
#include <iostream> //cout //stof
#include "number.h"


void Expression::serialize(json& jserialization){
  jserialization["objectName"] = objectName;
  jserialization["representation"] = representation;

  json jRegisterOfSlots;
  slots.serialize(jRegisterOfSlots);
  jserialization["slots"] = jRegisterOfSlots;

  json jMorph;
  myMorph.serialize(jMorph);
  jserialization["myMorph"] = jMorph;

  jserialization["type"] = "expression";

  //Agrego lo de expression

  if(receiver != nullptr) {
    json jReceiver;
    receiver->serialize(jReceiver);
    jserialization["receiver"] = jReceiver;
  } else
    jserialization["receiver"] = "nullptr";

  jserialization["operation"] = operation;

  if(argument != nullptr) {
    json jArgument;
    argument->serialize(jArgument);
    jserialization["argument"] = jArgument;
  } else
    jserialization["argument"] = "nullptr";

  if(result != nullptr) {
    json jResult;
    result->serialize(jResult);
    jserialization["result"] = jResult;
  }else
    jserialization["result"] = "nullptr";
}

//Deserealizacion

Expression* Expression::deserialize(json& jdeserialization, Lobby* lobby){
  Expression* expression = new Expression();
  expression->objectName = jdeserialization["objectName"];
  expression->representation = jdeserialization["representation"];

  json jRegisterOfSlots;
  jRegisterOfSlots = jdeserialization["slots"];
    expression->slots.deserialize(jRegisterOfSlots, expression, lobby);

  json jMorph;
  jMorph = jdeserialization["myMorph"];
  expression->myMorph.deserialize(jMorph);

  expression->myLobby = lobby;


    json jReceiver = jdeserialization["receiver"];
  if (jReceiver != "nullptr"){
    if (jReceiver["type"] == "number"){
      Object* object = Number::deserialize(jReceiver, lobby);
      expression->setReceiver(object);
    }
    else if (jReceiver["type"] == "searcherObject"){
      Object* object = SearcherObject::deserialize(jReceiver, lobby);
      expression->setReceiver(object);
    }
  }
  else{
    expression->receiver = nullptr;
  }

  expression->operation = jdeserialization["operation"];
  json jArgument = jdeserialization["argument"];
  if (jArgument != "nullptr"){
    if (jArgument["type"] == "number"){
      Object* object = Number::deserialize(jArgument, lobby);
      expression->setArgument(object);
    }
    else if (jArgument["type"] == "searcherObject"){
      Object* object = SearcherObject::deserialize(jArgument, lobby);
      expression->setArgument(object);
    }
  }
  else{
    expression->argument = nullptr;
  }

  return expression;
}



/*Esta clase modela un Composite*/
Expression::Expression(){
  receiver = nullptr;
  argument = nullptr;
  result = nullptr;
}

Expression::~Expression(){}


std::vector<Object*> Expression::getAtributs(){
  std::vector<Object*> v;
  if (receiver != nullptr){
    v.push_back(receiver);
    v.push_back(argument);
  }
  return v;
}


void Expression::setReceiver(Object* receiverPtr){
  receiver = receiverPtr;
  receiver->addSlots("self",this,false,true);
}

void Expression::setArgument(Object* argumentPtr){
  argument = argumentPtr;
  argument->addSlots("self",this,false,true);
}

void Expression::setOperator(std::string operatorString){
  this->operation = operatorString;
}


std::string Expression::getRepresentation() const {
  if ( receiver != nullptr){
    return "(" + receiver->getRepresentation() + operation + argument->getRepresentation() + ")";
  }
  return objectName;
}

NativeValue Expression::getValue(){
  if(result != nullptr){
    return result->getValue();
  }
  NativeValue value;
  return value;
}

Object* Expression::getResult(){
  if(result != nullptr){
    return result;
  }
  return this;
}



NativeValue Expression::ejecute(std::string operationStr, Object* argumentPtr){
  /*A la expression ya se le mando el mensaje evaluate, ahora pide ejecutar*/
  if(result!=nullptr){
    return result->ejecute(operationStr,argumentPtr);
  }
  /*Corregir esto luego*/
  NativeValue valueAux;
  return valueAux;
}

void Expression::setResult(Object* resultPtr){
  result = resultPtr;
}

std::vector<Object*> Expression::getReferences(){
  RegisterOfSlots slots = this->getSlots();
  std::vector<Object*> references =  slots.getObjectsNotParent();
  if (receiver != nullptr){
    references.push_back(receiver);
    references.push_back(argument);
  }
  if (result != nullptr){
    references.push_back(result);
  }
  return references;
}


Object* Expression::clone() const {
  Expression* newExpression = new Expression;
  if (receiver != nullptr){
    newExpression->setReceiver(receiver->clone());
  }
  if(argument != nullptr){
    newExpression->setArgument(argument->clone());
  }
  if (result != nullptr){
    newExpression->setResult(result->clone());
  }
  newExpression->setOperator(operation);
  newExpression->setName(objectName);
  return newExpression;
}

void Expression::evaluate(){
    if (receiver != nullptr){
      receiver->evaluate();
      argument->evaluate();
      NativeValue valor = receiver->ejecute(operation,argument->getResult());
      this->result = new Number(valor.getInt());
    }
    else{
      if(operation.compare("") != 0){
        Object* metodo = this->getSlotName(operation);
        std::cout << "objectName del metodo:" <<metodo->getName()<< std::endl;
        metodo->evaluate();
        this->setResult(metodo->getResult());
      }
    }
}

Object* Expression::searchForId(int objectId){
  std::cout << "Busco " << objectId << " en " << this->getName() << std::endl;
  std::cout << "Busco " << objectId << " mi ID: " << this->getMorphId() << std::endl;

    if(result != nullptr)
        if(objectId == result->getMorphId())
            return result;

  if(this->getMorphId() == objectId)return this;
  std::vector<Object*> mySlotsObjects = this->slots.getObjectsWhitoutParents(); //Para que no haya ciclos de busqueda
  for(auto itObjectSlot = mySlotsObjects.begin(); itObjectSlot != mySlotsObjects.end(); itObjectSlot++){
    if((*itObjectSlot)->getName() != "self") {
      Object *objectFound = (*itObjectSlot)->searchForId(objectId);
      if (objectFound != nullptr) return objectFound;
    }
  }
  return nullptr;
}
