#include "number.h"
#include <iostream> //cout //stof
#include "nativevalue.h"
#include "object.h"

Number::Number(int valueAux):Object(){
  value.setValue(valueAux);
  setReceiver(this);
  setResult(this);
}

Number::~Number(){}


void Number::setValue(int valueAux){
  /*Un nativeValue no es modificable*/
  //value = valueAux;
}

NativeValue Number::getValue(){
  return value;
}


void Number::evaluate(){

}

NativeValue Number::convertToNativeValue(){
  return getValue();
}


NativeValue Number::ejecute(std::string operation, Expression* expression){
  /*Aca permito cosas del tipo 3 + 4.0*/
  int resultado = 0;
  if (expression->getValue().isInt() || expression->getValue().isFloat()){
    std::cout << "Soy expression Number "<< value.getInt() <<" y voy a ejecutar la operation:" <<operation<< std::endl;
    if (operation.compare("*")==0){
      resultado = value.getInt()*expression->getValue().getInt();
    }else{
      resultado = value.getInt()+expression->getValue().getInt();
    }
  }else{
    std::cout << "Number::ejecute() cannot aplicate operation" <<operation<<"NativeValue is not typeCorrect"<< std::endl;
  }
  NativeValue value;
  value.setValue(resultado);
  return value;
}
