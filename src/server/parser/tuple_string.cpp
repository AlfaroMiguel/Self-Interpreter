#include "tuple_string.h"



using std::string;
TupleString::TupleString(string id,string message,string value):myId(id),myMessage(message),myValue(value){}

string TupleString::getiD(){
  return myId;
}

string TupleString::getValue(){
  return myValue;
}

string TupleString::getMessage(){
  return myMessage;
}

TupleString::~TupleString(){}
