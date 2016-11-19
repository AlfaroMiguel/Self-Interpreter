#include "expression.h"
#include "object.h"
#include <iostream> //cout //stof
#include "number.h"


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
  //Hay que arreglar esto sino no anda
  if ( receiver != nullptr){
    //std::cout << "objectName del receiver" << receiver->getName() << std::endl;
    return "(" + receiver->getRepresentation() + operation + argument->getRepresentation() + ")";
  }
  std::string pepe = "lala";
  return pepe;
}

NativeValue Expression::getValue(){
  return result->getValue();
}

Object* Expression::getResult(){
  return result;
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
    //std::cout << "Expression::evaluate" <<receiver->getName()<< std::endl;
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
    }
}
