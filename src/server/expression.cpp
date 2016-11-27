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
    jserialization["receiver"] = nullptr;

  jserialization["operation"] = operation;

  if(argument != nullptr) {
    json jArgument;
    argument->serialize(jArgument);
    jserialization["argument"] = jArgument;
  } else
    jserialization["argument"] = nullptr;

  if(result != nullptr) {
    json jResult;
    result->serialize(jResult);
    jserialization["result"] = jResult;
  }else
    jserialization["result"] = nullptr;
}

//Deserealizacion

Expression* Expression::deserialize(json& jdeserialization, Lobby* lobby){
  std::cout << "Expression::deserialize start" << std::endl;
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


  //Empieza expression
  json jReceiver = jdeserialization["receiver"];
  if(jdeserialization["type"] == "number" && jReceiver != nullptr)
    expression->receiver = Number::deserialize(jReceiver, lobby);
  else if(jdeserialization["type"] == "searcherObject" && jReceiver != nullptr)
    expression->receiver = SearcherObject::deserialize(jReceiver, lobby);
  else
    expression->receiver = nullptr;

  expression->operation = jdeserialization["operation"];

  json jArgument = jdeserialization["argument"];
  if(jdeserialization["type"] == "number" && jArgument != nullptr)
    expression->argument = Number::deserialize(jArgument, lobby);
  else if(jdeserialization["type"] == "searcherObject" && jArgument != nullptr)
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

/*Se setea el receiver y se le agrega el slot self*/
void Expression::setReceiver(Object* receiverPtr){
  std::cout << "Expression::setReceiver" << std::endl;
  receiver = receiverPtr;
  receiver->addSlots("self",this,false,true);
}

/*Se setea el argument y se le agrega el slot self*/
void Expression::setArgument(Object* argumentPtr){
  std::cout << "Expression::setArgument" << std::endl;
  argument = argumentPtr;
  argument->addSlots("self",this,false,true);
}

/*Se setea la operation que se va a ejecutar*/
void Expression::setOperator(std::string operatorString){
  std::cout << "Expression::setOperator" << std::endl;
  this->operation = operatorString;
}

/*De forma recursiva va pidiendo la representacion de sus componentes para
devolver su representacion*/
std::string Expression::getRepresentation() const {
  std::cout << "Expression::getRepresentation a: "<< objectName << std::endl;
  //Hay que arreglar esto sino no anda
  if ( receiver != nullptr){
    //std::cout << "objectName del receiver" << receiver->getName() << std::endl;
    return "(" + receiver->getRepresentation() + operation + argument->getRepresentation() + ")";
  }
  std::string pepe = "";
  return pepe;
}

/*Devuelve el NativeValue del result luego de evaluar la expression*/
NativeValue Expression::getValue(){
  return result->getValue();
}

Object* Expression::getResult(){
  return result;
}



/*Esto permite que se pueda acoplar mas mensaje a una expression que ya fue evaluada*/
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


/*Devuelve una copia de si mismo*/
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

/*Envia el mensaje a receiver con el argument seteado*/
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
      Object* metodo = this->getSlotName(operation);
      std::cout << "objectName del metodo:" <<metodo->getName()<< std::endl;
      metodo->evaluate();
      std::cout << "Resultado final:" <<metodo->getResult()->getValue().getInt()<< std::endl;
      this->setResult(metodo->getResult());
    }
}
