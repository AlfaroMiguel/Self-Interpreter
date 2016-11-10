#include "expression.h"
#include <iostream> //cout //stof
#include "number.h"


Expression::Expression(){}

Expression::~Expression(){}

void Expression::setReceiver(Expression* receiverPtr){
  receiver = receiverPtr;
}

void Expression::setArgument(Expression* argumentPtr){
  argument = argumentPtr;
}

void Expression::setOperator(std::string operatorString){
  this->operation = operatorString;
}

NativeValue Expression::getValue(){
  return result->getValue();
}

Expression* Expression::getResult(){
  return result;
}

NativeValue Expression::ejecute(std::string operationStr, Expression* argumentPtr){
  std::cout << "Error, cannot ejecute() in Expression class" << std::endl;
  /*A la expression ya se le mando el mensaje evaluate, ahora pide ejecutar*/
  if(result!=nullptr){
    return result->ejecute(operationStr,argumentPtr);
  }
  /*Corregir esto luego*/
  NativeValue valueAux;
  return valueAux;
}

Expression* Expression::getSlot(){
  std::cout <<"My name:"<<name<< "  getSlot:"<< std::endl;
  Expression* slot = mySlots.rbegin()->second;
  std::cout << "Slot name:" <<slot->getName()<< std::endl;
  return slot;
}

std::string Expression::getName(){
  return name;
}

void Expression::addSlots(std::string id,Expression* slot, bool algo, bool otro){
  std::cout <<"My name:"<<name<< " Agregado slot:" <<id<< std::endl;
  mySlots.insert(std::pair<std::string,Expression*>(id,slot));
}

void Expression::setName(std::string nameStr){
  std::cout << "Expression::setName:" <<nameStr<< std::endl;
  name = nameStr;
}
void Expression::setResult(Expression* resultPtr){
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
      Expression* metodo = this->mySlots[operation];
      std::cout << "nombre del metodo:" <<metodo->getName()<< std::endl;
      metodo->evaluate();
    }
}
