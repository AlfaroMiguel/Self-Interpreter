#include "expression.h"
#include "object.h"
#include <iostream> //cout //stof
#include "number.h"


void Expression::serialize(json& jserialization){
  std::cout << "Expression::serialize start:" << objectName << std::endl;
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
  std::cout << "Expression::deserialize start" << std::endl;
  Expression* expression = new Expression();
  expression->objectName = jdeserialization["objectName"];
  std::cout << "My nameeeee:" <<expression->objectName<< std::endl;
  expression->representation = jdeserialization["representation"];

  json jRegisterOfSlots;
  jRegisterOfSlots = jdeserialization["slots"];
  expression->slots.deserialize(jRegisterOfSlots, expression, lobby);

  json jMorph;
  jMorph = jdeserialization["myMorph"];
  expression->myMorph.deserialize(jMorph);

  expression->myLobby = lobby;


  //Empieza expression
  json jReceiver = jdeserialization["receiver"];
  std::cout << "el json receiver" <<jReceiver<< std::endl;
  if(jReceiver["type"] == "number" && jReceiver != "nullptr"){
    std::cout << "es del tipo number sasasasaasasasa" << std::endl;
    expression->receiver = Number::deserialize(jReceiver, lobby);
  }
  else if(jReceiver["type"] == "searcherObject" && jReceiver != "nullptr"){
    expression->receiver = SearcherObject::deserialize(jReceiver, lobby);
    std::cout << "es del tipo SearcherObject sasasasaasasasa" << std::endl;
  }
  else
    expression->receiver = nullptr;

  expression->operation = jdeserialization["operation"];

  json jArgument = jdeserialization["argument"];
  std::cout << "el json argument" <<jArgument<< std::endl;
  if(jArgument["type"] == "number" && jArgument != "nullptr")
    expression->argument = Number::deserialize(jArgument, lobby);
  else if(jArgument["type"] == "searcherObject" && jArgument != "nullptr")
    expression->argument = SearcherObject::deserialize(jArgument, lobby);
  else
    expression->argument = nullptr;

  json jResult = jdeserialization["result"];
  if(jdeserialization["type"] == "number" && jResult != nullptr)
    expression->result = Number::deserialize(jResult, lobby);
  else if(jdeserialization["type"] == "searcherObject" && jResult != nullptr)
    expression->result = SearcherObject::deserialize(jResult, lobby);
  else
    expression->result = nullptr;

  std::cout << "Expression::deserialize end" << std::endl;

  return expression;
}



/*Esta clase modela un Composite*/
Expression::Expression(){
  receiver = nullptr;
  argument = nullptr;
  result = nullptr;
  if (receiver != nullptr){
    std::cout << "receive not null" << std::endl;
  }
  if (argument != nullptr){
    std::cout << "argument not null" << std::endl;
  }
}

Expression::~Expression(){}


std::vector<Object*> Expression::getAtributs(){
  std::cout << "/* Expression::getAtributs*/" << std::endl;
  std::vector<Object*> v;
  if (receiver != nullptr){
    std::cout << "dentro de if" << std::endl;
    v.push_back(receiver);
    v.push_back(argument);
  }
  return v;
}


void Expression::setReceiver(Object* receiverPtr){
  std::cout << "Expression::setReceiver" << std::endl;
  receiver = receiverPtr;
  receiver->addSlots("self",this,false,true);
}

void Expression::setArgument(Object* argumentPtr){
  std::cout << "Expression::setArgument" << std::endl;
  argument = argumentPtr;
  argument->addSlots("self",this,false,true);
}

void Expression::setOperator(std::string operatorString){
  std::cout << "Expression::setOperator" << std::endl;
  this->operation = operatorString;
}


std::string Expression::getRepresentation() const {
  std::cout << "Expression::getRepresentation a: "<< objectName << std::endl;
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
    std::cout << "/* result es distinto de nulltpr */" << std::endl;
    return result;
  }
  return this;
}



NativeValue Expression::ejecute(std::string operationStr, Object* argumentPtr){
  std::cout << "Error, cannot ejecute() in Expression class" << std::endl;
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


Object* Expression::clone(){
  std::cout << "Expression::clone" << std::endl;
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
    std::cout << "Expression::evaluate" << std::endl;
    if (receiver != nullptr){
      std::cout << "dentro del if" << std::endl;
      receiver->evaluate();
      argument->evaluate();
      NativeValue valor = receiver->ejecute(operation,argument->getResult());
      this->result = new Number(valor.getInt());
      std::cout << "Resultado de la expression:" << result->getValue().getInt() << std::endl;
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
