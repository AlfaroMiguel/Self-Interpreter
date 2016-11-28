#include "interpreter.h"
#include <iostream> //cout //stof
#include "../virtualmachine/object.h"
#include "../virtualmachine/number.h"
#include "../virtualmachine/searcher_object.h"
#include <string>
#include "scanner.h"
#include <vector>
#include <stdexcept>
#include "../virtualmachine/morph.h"
#include "../virtualmachine/lobby.h"

extern int yyparse(Interpreter *interpreter);

extern FILE *yyin;

extern void reset_lexer(void);

extern void reset_parser(void);
extern int yylex_destroy(void);

using std::string;



Interpreter::Interpreter(Object *lobbyObjectPtr, Lobby *lobby) : lobbyObject(lobbyObjectPtr), lobby(lobby),garbage(lobbyObjectPtr){
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
    mapMessages.insert(std::pair<string, int>("error", 17));
    isClone = false;
    parentClone = nullptr;
}

void Interpreter::pushToken(const string id, const string message, const string value) {
    int id_message = mapMessages[message];
    switch (id_message) {
        case 1:
            createNumber(value);
            break;
        case 2:
            assignationExpression(id);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            stack.push(findExpression(id));
            break;
        case 6:
            break;
        case 7:
            encapsulateStack();
            break;
        case 8:
            addSlot(id);
            break;
        case 9:
            removeSlot(id);
            break;
        case 10:
            createExpression(message);
            break;
        case 11:
            createExpression(message);
            break;
        case 12:
            createExpression(message);
            break;
        case 13:
            createExpression(message);
            break;
        case 14:
            createVariable(id);
            break;
        case 15:
            setRepresentation(value);
            break;
        case 16:
              cloneObject(id);
              break;
        case 17:
              emptyStack();
              break;
        default:
            reportFile << "Message not found: " + message + "\n";
            sendMessage(message);
    }
}



void Interpreter::registerObject(Object* object){
    garbage.registerObject(object);
    std::vector<Object*> slots = object->getReferences();
    for (size_t i = 0; i < slots.size(); i++) {
        std::cout << "slot de nombre:" <<slots[i]->getName()<<"de:"<<object->getName()<< std::endl;
        registerObject(slots[i]);
  }
}

void Interpreter::registerObjects(){
  std::vector<Object*> slots = lobbyObject->getReferences();
  for (size_t i = 0; i < slots.size(); i++) {
    registerObject(slots[i]);
  }
}


void Interpreter::emptyStack(){
  std::cout << "Error de sintaxis" << std::endl;
  while(!stack.empty()){
    stack.pop();
  }
}

void Interpreter::removeSlot(const std::string name){
  reportFile << "Message not found: " + name + "\n";
  Object* objectToDeleteSlots = findExpression(name);
  //es un object modificado
  modifiedObjects.push_back(objectToDeleteSlots);
  Object* objectEncapsulate = stack.top();
  stack.pop();
  RegisterOfSlots slots = objectEncapsulate->getSlots();
  std::vector<Object*> slotsVector = slots.getObjects();
  //se puede eliminar varios slots
  for (size_t i = 0; i < slotsVector.size(); i++) {
    Object* slot = slotsVector[i];
    std::string nameSlot = slot->getName();
    reportFile << "name of slot to delete:"+nameSlot+ "\n";
    objectToDeleteSlots->RemoveSlots(nameSlot);
  }
}

void Interpreter::cloneObject(const std::string id){
    isClone = true;
    reportFile << "Interpreter::cloneObject:"+id+"\n";
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
    reportFile << "cantidad de slots nativos:" +std::to_string(slotsVector.size())+"\n";
    for (size_t i = 0; i < slotsVector.size(); i++){
      bool isFound = false;
      Object* slotNative = slotsVector[i];
      reportFile<< "Slot native name" + slotNative->getName()+"\n" ;
      for (size_t j = 0; j < slotsRedefined.size(); j++){
        Object* slotRedefined = slotsRedefined[j];
        //si un slot fue redefinido
        if (slotNative->getName().compare(slotRedefined->getName()) == 0){
          isFound = true;
        }
      }
      //si el slot nativo no esta entre los redefinidos entonces lo agrego
      if(!isFound){
        reportFile << "Slot not found" <<slotNative->getName()<< "\n";
        Object* newSlot = garbage.cloneObject(slotNative);
        stack.push(newSlot);
    }
  }
  //reagrego los slots redefinidos en el stack
  for (size_t i = 0; i < slotsRedefined.size(); i++) {
    Object* slot = slotsRedefined[i];
    stack.push(slot);
  }
  reportFile << "Tamaño del stack:" + std::to_string(stack.size())+ "despues de clonar el objeto\n";
  if (stack.size() == slotsVector.size()){
    reportFile << "la cantidad es correcta\n";
  }

}
void Interpreter::setRepresentation(const std::string value) {
    Object *object = stack.top();
    object->setRepresentation(value);
}


void Interpreter::sendMessage(const string message){
    reportFile << "sendMessage\n";
    Object *expression = stack.top();
    reportFile << "Nombre de expression a enviar mensaje:" + expression->getName() + "\n";
    stack.pop();
    /*tengo que ver cuando tengo mas de un argumento*/
    expression->setOperator(message);
    expression->evaluate();
    Object* result = expression->getResult();
    garbage.registerObject(result);
    reportFile << "Interpreter::name" <<result->getName()<< "\n";
    std::string resultSTR = result->getRepresentation();
    std::string name = message; //TESTLINEA
    result->myMorph.setUnionName(name); //TESTLINEA
    result->changeMorphName(resultSTR); //TEST
    result->myMorph.setUnionId(expression->getMorphId()); //TEST LINEA
    createdObjects.push_back(result);
    result->setLobby(lobby);
}

void Interpreter::createNumber(const string value) {
    reportFile << "createNumber: " << value << "\n";
    Object* number = garbage.createNumber(value);
    stack.push(number);
}

void Interpreter::createVariable(const string name) {
    reportFile << "createVariable" << "\n";
    Object* object = garbage.createSearcherObject(name);
    stack.push(object);
}

void Interpreter::createExpression(const string message) {
    reportFile << "Interpreter::createExpression: " << message << "\n";
    reportFile << "Tamaño del stack:" <<stack.size()<< "\n";
    Object* expression = garbage.createExpression();
    expression->setArgument(stack.top());
    stack.pop();
    expression->setOperator(message);
    expression->setReceiver(stack.top());
    stack.pop();
    stack.push(expression);
}

Object *Interpreter::findExpression(const string name) {
    reportFile << "findExpression:" << name << "\n";
    if (name.compare("lobby") == 0) {
        return lobbyObject;
    }
    if (name.compare("self") == 0){
      return entorno;
    }
    Object *object = lobbyObject->getSlotName(name);
    if (object != nullptr) {
        return object;
    } else {
        throw std::runtime_error("Interpreter::objectReference no encontrado");
    }
}

void Interpreter::assignationExpression(const string name) {
    reportFile << "assginationExpression: " + name + "\n";
    if (!stack.empty()) {
        Object *expression = stack.top();
        expression->setName(name);
        expression->setLobby(lobby);

        reportFile << "Get representation: " + expression->getRepresentation() + "\n";
    } else {
        reportFile << "Hubo un error no existe objectReference al cual asignar objectName\n";
    }
}

void Interpreter::encapsulateStack() {
    reportFile << "Tamaño del stack:" +std::to_string(stack.size())+ "\n";
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

void Interpreter::addSlot(const string name) {
    reportFile << "addSlot: " + name + "\n";
    //Objeto a la que voy agregar slot
    Object *parent = findExpression(name);
    modifiedObjects.push_back(parent);
    //Objeto a la que le saco el slot
    Object *expressionSlotRemove = stack.top();
    stack.pop();
    RegisterOfSlots slots = expressionSlotRemove->getSlots();
    std::vector<Object *> slotsVector = slots.getObjects();
    Object *slot = slotsVector[0];
    parent->addSlots(slot->getName(), slot, false, false);
    reportFile << "Se creo elemento: " + slot->getName() + "\n";
    createdObjects.push_back(slot);
    slot->addSlots("self", parent, false, true);
    if (name.compare("lobby") == 0) {
        reportFile << "Lo guarde en el lobby\n";
        map.insert(std::pair<string, Object *>(slot->getName(), slot));
    }
    Morph::idNumber--;
}

void Interpreter::clearVectors(){
  createdObjects.clear();
  modifiedObjects.clear();
}

void Interpreter::interpretChar(const char *buffer,Object* entorno_ptr) {
    entorno = entorno_ptr;
    reportFile.open("Interpreter_LOG.txt",std::ofstream::app);
    clearVectors();
    std::string bufferToInterpreter(buffer);
    reportFile << "Empieza a interpretar:" +bufferToInterpreter+"\n";
    yy_scan_string(buffer);
    int resultado = yyparse(this);
    std::cout << "El resultado del parser es:" <<resultado<< std::endl;
    reportFile << "Termine de interpretar\n";
    reportFile << "Se llama al recolector de basura\n";
    yylex_destroy();
    garbage.collect();
    reportFile.close();
}

std::vector<Object*> Interpreter::getCreatedObjets(){
  reportFile.open("Interpreter_LOG.txt",std::ofstream::app);
  reportFile  << "Objetos creados\n";
  for (size_t i = 0; i < createdObjects.size(); i++) {
    reportFile << "      *Nombre:"+ createdObjects[i]->getName()+"\n";
  }
  reportFile.close();
  return createdObjects;
}

std::vector<Object*> Interpreter::getModifiedObjets(){
    reportFile.open("Interpreter_LOG.txt",std::ofstream::app);
    reportFile  << "Objetos modificados\n";
    std::cout  << "Objetos modificados\n";
    for (size_t i = 0; i < modifiedObjects.size(); i++) {
        reportFile << "      *Nombre:"+ modifiedObjects[i]->getName()+"\n";
  }
    reportFile.close();
    return modifiedObjects;
}

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
