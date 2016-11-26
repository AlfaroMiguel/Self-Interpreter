#include "interpreter.h"
#include <iostream> //cout //stof
#include "../object.h"
#include "../number.h"
#include "../searcher_object.h"
#include <string>
#include "scanner.h"
#include <vector>
#include <stdexcept>
#include "../lobby.h"

extern int yyparse(Interpreter *interpreter);

extern FILE *yyin;

extern void reset_lexer(void);

extern void reset_parser(void);

using std::string;


/*Se crea un interpreter y se carga todos los tipos de mensajes que puede llegar
a recibir por parte de Parser*/
Interpreter::Interpreter(Object *entorno_ptr, Lobby *lobby) : entorno(entorno_ptr), lobby(lobby),garbage(entorno_ptr){
    mapMessages.insert(std::pair<string, int>("create_number", 1));
    mapMessages.insert(std::pair<string, int>("assignation", 2));
    mapMessages.insert(std::pair<string, int>("assignation_mutable", 3));
    mapMessages.insert(std::pair<string, int>("print", 4));
    mapMessages.insert(std::pair<string, int>("find", 5));
    mapMessages.insert(std::pair<string, int>("set", 6));
    mapMessages.insert(std::pair<string, int>("encapsulate", 7));
    mapMessages.insert(std::pair<string, int>("add", 8));
    mapMessages.insert(std::pair<string, int>("remove", 9));
    mapMessages.insert(std::pair<string, int>("+", 10));
    mapMessages.insert(std::pair<string, int>("-", 11));
    mapMessages.insert(std::pair<string, int>("*", 12));
    mapMessages.insert(std::pair<string, int>("/", 13));
    mapMessages.insert(std::pair<string, int>("create_variable", 14));
    mapMessages.insert(std::pair<string, int>("representation", 15));
    mapMessages.insert(std::pair<string, int>("clone", 16));
    isClone = false;
    parentClone = nullptr;
}

/*Este el método que invoca Parser, acá se identifica cuál es el mensaje y se
lo ejecuta*/
void Interpreter::pushToken(string id, string message, string value) {
    int id_message = mapMessages[message];
    switch (id_message) {
        case 1:
            createNumber(value);
            break;
        case 2:
            assignationExpression(id);
            break;
        case 3:
            std::cout << "Create null Expression mutal and assignation" << std::endl;
            break;
        case 4:
            std::cout << "Expression [print]" << std::endl;
            break;
        case 5:
            std::cout << "Find Expression" << std::endl;
            stack.push(findExpression(id));
            break;
        case 6:
            std::cout << "Expression [set]" << std::endl;
            break;
        case 7:
            std::cout << "Encapsulate stack" << std::endl;
            encapsulateStack();
            break;
        case 8:
            std::cout << "Expression [add_slot]" << std::endl;
            addSlot(id);
            break;
        case 9:
        removeSlot(id);
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
        case 14:
            //std::cout<<"Expression [division] Expression"<<std::endl;
            createVariable(id);
            break;
        case 15:
            //std::cout<<"Expression [division] Expression"<<std::endl;
            setRepresentation(value);
            break;
        case 16:
                //std::cout<<"Expression [division] Expression"<<std::endl;
              cloneObject(id);
              break;
        default:
            std::cout << "Interpreter::ERROR: message not found: " << message << std::endl;
            sendMessage(message);
    }
}


void Interpreter::removeSlot(std::string name){
  Object* objectToDeleteSlots = findExpression(name);
  Object* objectEncapsulate = stack.top();
  stack.pop();
  RegisterOfSlots slots = objectEncapsulate->getSlots();
  std::vector<Object*> slotsVector = slots.getObjects();
  for (size_t i = 0; i < slotsVector.size(); i++) {
    Object* slot = slotsVector[i];
    std::string nameSlot = slot->getName();
    std::cout << "name of slots"<<nameSlot<< std::endl;
    objectToDeleteSlots->RemoveSlots(nameSlot);
    //delete(slot);
  }
  //delete(objectEncapsulate);
  temporalObjects.push_back(objectToDeleteSlots);
}

/*Dado que se quiere clonar un objeto se lo busca en el lobby y se clona todos
sus slots, tambien se guarda el estado isClone para luego guardarle el slot
parent*/
void Interpreter::cloneObject(std::string id){
    isClone = true;
    std::cout << "Interpreter::cloneObject(" <<id<<")"<< std::endl;
    Object* objectToClone = findExpression(id);
    parentClone = objectToClone;
    RegisterOfSlots slots = objectToClone->getSlots();
    std::vector<Object*> slotsVector = slots.getObjectsNotParent();
    std::vector<Object*> slotsRedefined;
    //Saco todos los slots que se redefinieron (colocar un iterator)
    while (!stack.empty()) {
      slotsRedefined.push_back(stack.top());
      stack.pop();
    }
    //si un un slot nativo estan entre los que se redefinio entonces guardo el
    //redefinido, sino creo un copia y lo inserto
    std::cout << "cantidad de slots nativos" <<slotsVector.size()<< std::endl;
    for (size_t i = 0; i < slotsVector.size(); i++){
      bool isFound = false;
      Object* slotNative = slotsVector[i];
      std::cout << "Slot native name" <<slotNative->getName()<< std::endl;
      for (size_t j = 0; j < slotsRedefined.size(); j++){
        Object* slotRedefined = slotsRedefined[j];
        //si un slot fue redefinido
        if (slotNative->getName().compare(slotRedefined->getName()) == 0){
          isFound = true;
        }
      }
      //sino esta entre los redefinidos entonces lo agrego
      if(!isFound){
        std::cout << "Slot not found" <<slotNative->getName()<< std::endl;
        //Object* newSlot = slotNative->clone();
        Object* newSlot = garbage.cloneObject(slotNative);
        stack.push(newSlot);
    }
  }
  //reagrego los slots redefinidos en el stack
  for (size_t i = 0; i < slotsRedefined.size(); i++) {
    Object* slot = slotsRedefined[i];
    stack.push(slot);
  }
  std::cout << "Tamaño del stack:" <<stack.size()<<"despues de clonar el objeto"<< std::endl;
  if (stack.size() == slotsVector.size()){
    std::cout << "la cantidad es correcta" << std::endl;
  }

}
/*En caso de que me pidan redefinir un objeto, saco el objeto del stack que se
supone que es el objeto al cual se mando el mensaje*/
void Interpreter::setRepresentation(std::string value) {
    Object *object = stack.top();
    object->setRepresentation(value);
}


/*Cunado se invoca un método de un objeto, se supone que este la cabeza del stack
se setea la operacion que debe realizar y se pide que se evalue, luego se le pide
el resultado para que muestre graficamente*/
void Interpreter::sendMessage(string message){
    std::cout << "sendMessage" << std::endl;
    Object *expression = stack.top();
    std::cout << "Nombre de expression a enviar mensaje:" << expression->getName() << std::endl;
    stack.pop();
    /*tengo que ver cuando tengo mas de un argumento*/
    expression->setOperator(message);
    expression->evaluate();
    Object* result = expression->getResult();
    garbage.registerObject(result);
    std::cout << "Interpreter::resultado" <<result->getValue().getInt()<< std::endl;
    temporalObjects.push_back(result);
    result->setLobby(lobby);
}

/*Se crea un numero con el el valor que se encuentre en el string*/
void Interpreter::createNumber(string value) {
    std::cout << "createNumber: " << value << std::endl;
    //Number *number = new Number(stof(value));
    Object* number = garbage.createNumber(value);
    stack.push(number);
}

/*Se crea una variable con un objeto del SearcherObject que luego buscar en su
entorno a que tipo corresponde*/
void Interpreter::createVariable(string name) {
    std::cout << "createVariable" << std::endl;
    //SearcherObject *object = new SearcherObject(name);
    Object* object = garbage.createSearcherObject(name);
    stack.push(object);
}

/*Aca se crea una expression generica y se le setea el message, por eso se sabe que
 los 2 objetos que se encuentran son su receiver y argument*/
void Interpreter::createExpression(string message) {
    std::cout << "Interpreter::createExpression: " << message << std::endl;
    std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
    //Expression *expression = new Expression;
    Object* expression = garbage.createExpression();
    expression->setArgument(stack.top());
    stack.pop();
    expression->setOperator(message);
    expression->setReceiver(stack.top());
    stack.pop();
    stack.push(expression);
}

/*Si no se encuetra en el map, lo creo y lo devuelvo*/
Object *Interpreter::findExpression(string name) {
    std::cout << "findExpression:" << name << std::endl;
    if (name.compare("lobby") == 0) {
        return entorno;
    }
    Object *object = entorno->getSlotName(name);
    if (object != nullptr) {
        return object;
    } else {
        throw std::runtime_error("Interpreter::objectReference no encontrado");
    }
}

/*Se setea el nombre al objeto ultimo que se inserto en el stack*/
void Interpreter::assignationExpression(string name) {
    std::cout << "assginationExpression: " << name << std::endl;
    if (!stack.empty()) {
        Object *expression = stack.top();
        expression->setName(name);

        expression->setLobby(lobby); //Test

        std::cout << "Get representation: " << std::endl;
        std::cout << expression->getRepresentation() << std::endl;
    } else {
        std::cout << "Hubo un error no existe objectReference al cual asignar objectName" << std::endl;
    }
}

/*Todo lo que haya en el stack lo agrego como slot en un objectReference que lo agrego en el stack*/
void Interpreter::encapsulateStack() {
    std::cout << "Tamaño del stack:" <<stack.size()<< std::endl;
    //Expression* parent = new Expression;
    Object* parent = garbage.createExpression();
    while (!stack.empty()) {
        Object *slot = stack.top();
        stack.pop();
        parent->addSlots(slot->getName(), slot, false, false);
        slot->addSlots("self", parent, false, true);
    }
    if(isClone){
      parent->addSlots("parent", parentClone, false, true);
      isClone = false;
      parentClone = nullptr;
    }
    stack.push(parent);
}

/*Voy a tener algo expression addSlot algo, ese algo es un objectReference a la cual le
le pido sus slots y los agreago a objectReference*/
void Interpreter::addSlot(string name) {
    std::cout << "addSlot: " << name << std::endl;
    //Objeto a la que voy agregar slot
    Object *parent = findExpression(name);
    //Objeto a la que le saco el slot
    Object *expressionSlotRemove = stack.top();
    stack.pop();
    RegisterOfSlots slots = expressionSlotRemove->getSlots();
    std::vector<Object *> slotsVector = slots.getObjects();
    Object *slot = slotsVector[0];
    parent->addSlots(slot->getName(), slot, false, false);
    std::cout << "Se creo elemento: " << slot->getName() << std::endl;
    temporalObjects.push_back(slot);
    slot->addSlots("self", parent, false, true);
    if (name.compare("lobby") == 0) {
        std::cout << "Lo guarde en el lobby" << std::endl;
        map.insert(std::pair<string, Object *>(slot->getName(), slot));
    }
    //delete(expressionSlotRemove);
}
/*Este metodo es invocado por el server para que interprete un cadena*/
std::vector<Object *> Interpreter::interpretChar(const char *buffer) {
    temporalObjects.clear();
    std::cout << "Empieza a interpretar" << buffer << std::endl;
    yy_scan_string(buffer);
    yyparse(this);
    std::cout << "Objectos notificados" << std::endl;
    for (size_t i = 0; i < temporalObjects.size(); i++) {
      std::cout << "Name:"<< temporalObjects[i]->getName()<< std::endl;
    }
    std::cout << "Termine de interpretar"<< std::endl;
    garbage.collect();
    return temporalObjects;
}

//Tiene que interpretar codigo de un archivo
void Interpreter::interpretFile(const char *nameFile) {
    FILE *file = fopen(nameFile, "r");
    if (file == NULL) {
        printf(" No se pudo abrir el archivo %s\n", nameFile);
        exit(0);
    }
    //yyin = file;
    //yyparse(); //TODO : A esta linea le falta un parametro
    fclose(file);
}

Interpreter::~Interpreter() {}
