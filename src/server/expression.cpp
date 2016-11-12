#include "expression.h"
#include "object.h"
#include <iostream> //cout //stof
#include "number.h"


Expression::Expression(){}

Expression::~Expression(){}

void Expression::setReceiver(Object* receiverPtr){
  receiver = receiverPtr;
}

void Expression::setArgument(Object* argumentPtr){
  argument = argumentPtr;
}

void Expression::setOperator(std::string operatorString){
  this->operation = operatorString;
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


void Expression::evaluate(){
    std::cout << "Expression::evaluate" << std::endl;
    //std::cout << "Expression::evaluate" <<receiver->getName()<< std::endl;
    if (receiver != nullptr){
      receiver->evaluate();
      argument->evaluate();
      NativeValue valor = receiver->ejecute(operation,argument->getResult());
      this->result = new Number(valor.getInt());
      std::cout << "Resultado de la expression:" << result->getValue().getInt() << std::endl;
    }
    else{
      Object* metodo = this->getSlotName(operation);
      std::cout << "nombre del metodo:" <<metodo->getName()<< std::endl;
      metodo->evaluate();
    }
}
