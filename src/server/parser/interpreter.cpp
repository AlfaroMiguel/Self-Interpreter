#include "interpreter.h"
#include <iostream> //cout //stof
#include "../object.h"
#include "../number.h"
#include <string>
#include "scanner.h"
#include <vector>

extern int yyparse();
extern FILE *yyin;
extern void reset_lexer(void);
extern void reset_parser(void);

using std::string;

Interpreter::Interpreter(){
  mapMessages.insert(std::pair<string,int>("create_number",1));
  mapMessages.insert(std::pair<string,int>("assignation",2));
  mapMessages.insert(std::pair<string,int>("assignation_mutable",3));
  mapMessages.insert(std::pair<string,int>("print",4));
  mapMessages.insert(std::pair<string,int>("find",5));
  mapMessages.insert(std::pair<string,int>("set",6));
  mapMessages.insert(std::pair<string,int>("encapsulate",7));
  mapMessages.insert(std::pair<string,int>("add",8));
  mapMessages.insert(std::pair<string,int>("remove",9));
  mapMessages.insert(std::pair<string,int>("+",10));
  mapMessages.insert(std::pair<string,int>("-",11));
  mapMessages.insert(std::pair<string,int>("*",12));
  mapMessages.insert(std::pair<string,int>("/",13));
  /*Lobby tiene existencia desde un principio*/
  Object* lobby = new Object;
  lobby->setName("lobby");
  map.insert(std::pair<string,Object*>(lobby->getName(),lobby));
}

/*id       message    valor
        create_number
  id    print
  id    assignation

  */


void Interpreter::pushToken(string id,string message, string value){
  //TupleString tuple(id,message,value);
  //myStack.push(tuple);
  int id_message = mapMessages[message];
  switch(id_message){
    case 1:
      createNumber(value);
      break;
    case 2:
        std::cout<<"assignation Expression"<<std::endl;
        assignationExpression(id);
        break;
    case 3:
        std::cout<<"Create null Expression mutal and assignation"<<std::endl;
        break;
    case 4:
        std::cout<<"Expression [print]"<<std::endl;
        break;
    case 5:
        std::cout<<"Find Expression"<<std::endl;
        stack.push(findExpression(id));
        break;
    case 6:
        std::cout<<"Expression [set]"<<std::endl;
        break;
    case 7:
        std::cout<<"Encapsulate stack"<<std::endl;
        encapsulateStack();
        break;
    case 8:
        std::cout<<"Expression [add_slot]"<<std::endl;
        addSlot(id);
        break;
    case 9:
        std::cout<<"Expression [remove_slot]"<<std::endl;
        break;
    case 10:
        //std::cout<<"Expression [sum] Expression"<<std::endl;
        createExpression(message);
        break;
    case 11:
        //std::cout<<"Expression [less] Expression"<<std::endl;
        createExpression(message);
        break;
    case 12:
        //std::cout<<"Expression [multiplication] Expression"<<std::endl;
        createExpression(message);
        break;
    case 13:
        //std::cout<<"Expression [division] Expression"<<std::endl;
        createExpression(message);
        break;
    default:
      std::cout<<"Interpreter::ERROR: message not found:"<<message<<std::endl;
      sendMessage(message);
  }
}

void Interpreter::end(){
  /*logica para cuanto tengo que ejecutar toda una linea*/
}

void Interpreter::sendMessage(string message){
  std::cout << "sendMessage" << std::endl;
  Object* expression = stack.top();
  std::cout << "Nombre de expression:" <<expression->getName()<< std::endl;
  stack.pop();
  /*tengo que ver cuando tengo mas de un argumento*/
  expression->setOperator(message);
  expression->evaluate();
}

void Interpreter::createNumber(string value){
  std::cout << "createNumber:"<<value<<std::endl;
  std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
  Number* number = new Number(stof(value));
  stack.push(number);
}


void Interpreter::createExpression(string message){
  std::cout << "createExpression:" <<message<< std::endl;
  std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
  Object* expression = new Object;
  expression->setArgument(stack.top());
  stack.pop();
  expression->setOperator(message);
  expression->setReceiver(stack.top());
  stack.pop();
  stack.push(expression);
}
/*Si no se encuetra en el map, lo creo y lo devuelvo*/
Object* Interpreter::findExpression(string name){
  std::cout << "findExpression:" <<name<< std::endl;
  if (map.count(name) == 0){
    std::cout << "not found" << std::endl;
      Object* expression = new Object;
      expression->setName(name);
      return expression;
    }
    return map[name];
}

/*Si existia un Expression, se piza sino no pasa nada*/
void Interpreter::assignationExpression(string name){
  std::cout << "assginationExpression"<< std::endl;
  std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
  if (!stack.empty()){
    Object* expression = stack.top();
    expression->setName(name);
  }else{
    std::cout << "Hubo un error no existe objeto al cual asignar nombre" <<std::endl;
    }
  }

/*Todo lo que haya en el stack lo agrego como slot en un objeto que lo agrego en el stack*/
void Interpreter::encapsulateStack(){
  Object* expression = new Object;
  std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
  while (!stack.empty()){
    Object* slot = stack.top();
    stack.pop();
    expression->addSlots(slot->getName(),slot,false,false);
  }
  stack.push(expression);
}

/*Voy a tener algo expression addSlot algo, ese algo es un objeto a la cual le
le pido sus slots y los agreago a objeto*/
void Interpreter::addSlot(string name){
  std::cout << "addSlot:"<<name<<std::endl;
  //Objeto a la que voy agregar slot
  Object* parent = findExpression(name);
  //Objeto a la que le saco el slot
  Object* expressionSlotRemove = stack.top();
  stack.pop();
  RegistroDeSlots slots = expressionSlotRemove->getSlots();
  std::vector<Object*> slotsVector = slots.getObjects();
  Object* slot = slotsVector[0];
  parent->addSlots(slot->getName(),slot,false,false);
  slot->addSlots(parent->getName(),parent,false,true);
  if(name.compare("lobby") == 0){
    std::cout << "Lo guarde en el lobby" << std::endl;
    map.insert(std::pair<string,Object*>(slot->getName(),slot));
  }
}

void Interpreter::interpretChar(char* buffer){
  yy_scan_string(buffer);
  yyparse();
}


void Interpreter::interpretFile(const char* nameFile){
  FILE * file = fopen(nameFile ,"r");
	if( file == NULL ) {printf (" couldn ’t open %s\n", nameFile); exit (0);}
	yyin = file ; // now flex reads from file
	yyparse();
	fclose(file);
}

Interpreter::~Interpreter(){}
