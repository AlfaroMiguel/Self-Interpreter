#include "tokenizer.h"
#include "tuple_string.h"
#include <iostream> //cout

using std::string;

Tokenizer::Tokenizer(){
  myMap.insert(std::pair<string,int>("create_number",1));
  myMap.insert(std::pair<string,int>("assignation",2));
  myMap.insert(std::pair<string,int>("assignation_mutable",3));
  myMap.insert(std::pair<string,int>("print",4));
  myMap.insert(std::pair<string,int>("find",5));
  myMap.insert(std::pair<string,int>("set",6));
  myMap.insert(std::pair<string,int>("encapsulate",7));
  myMap.insert(std::pair<string,int>("add",8));
  myMap.insert(std::pair<string,int>("remove",9));
  myMap.insert(std::pair<string,int>("+",10));
  myMap.insert(std::pair<string,int>("-",11));
  myMap.insert(std::pair<string,int>("*",12));
  myMap.insert(std::pair<string,int>("/",13));
}

/*id       message    valor
        create_number
  id    print
  id    assignation

  */


void Tokenizer::pushToken(string id,string message, string value){
  //TupleString tuple(id,message,value);
  //myStack.push(tuple);
  int id_message = myMap[message];
  switch(id_message){
    case 1:
      std::cout<<"Create a number object and push"<<std::endl;
      break;
    case 2:
        std::cout<<"Create null object not mutal and assignation"<<std::endl;
        break;
    case 3:
        std::cout<<"Create null object mutal and assignation"<<std::endl;
        break;
    case 4:
        std::cout<<"Object [print]"<<std::endl;
        break;
    case 5:
        std::cout<<"Find Object"<<std::endl;
        break;
    case 6:
        std::cout<<"Object [set]"<<std::endl;
        break;
    case 7:
        std::cout<<"Encapsulate stack"<<std::endl;
        break;
    case 8:
        std::cout<<"Object [add_slot]"<<std::endl;
        break;
    case 9:
        std::cout<<"Object [remove_slot]"<<std::endl;
        break;
    case 10:
        std::cout<<"Object [sum] Object"<<std::endl;
        break;
    case 11:
        std::cout<<"Object [less] Object"<<std::endl;
        break;
    case 12:
        std::cout<<"Object [multiplication] Object"<<std::endl;
        break;
    case 13:
        std::cout<<"Object [division] Object"<<std::endl;
        break;
    default:
      std::cout<<"ERROR: message not found:"<<message<<std::endl;
  }
}

void Tokenizer::end(){
  /*logica para cuanto tengo que ejecutar toda una linea*/
}

Tokenizer::~Tokenizer(){}
