#include "garbage_collector.h"

#include "number.h"
#include "searcher_object.h"
#include "expression.h"
#include <iostream> //cout //stof

GarbageCollector::GarbageCollector(Object* lobbyPtr):objectLobby(lobbyPtr),reportFile("Garbage_Collector_Report.txt",std::ofstream::out){
  registerObject(lobbyPtr);
}



GarbageCollector::~GarbageCollector(){
  std::cout << "destructor" << std::endl;
  reportFile.close();
}


void GarbageCollector::registerObject(Object* object){
  std::cout << "Se registro:" <<object->getName()<<"pointer"<<object<< std::endl;
  createdObjects.push_back(object);
}


Object* GarbageCollector::createNumber(std::string value){
  Number* newNumber = new Number(stof(value));
  registerObject(newNumber);
  return newNumber;
}


void GarbageCollector::markObject(Object* object){
  map.insert(std::pair<Object*, int>(object, 1));
}

Object* GarbageCollector::createSearcherObject(std::string name){
  SearcherObject* object = new SearcherObject(name);
  registerObject(object);
  return object;
}

Object* GarbageCollector::createExpression(){
  Expression* expression = new Expression;
  registerObject(expression);
  return expression;
}

void GarbageCollector::visit(Object* object){
  if (object != nullptr){
    std::cout << "distinto a nullptr" << std::endl;
    std::cout << "Object visit:" <<object->getName()<<","<< std::endl;
    markObject(object);
    std::vector<Object*> pointers = object->getReferences();
    std::cout << "Cantidad a visitar:" <<pointers.size()<< std::endl;
    for (size_t i = 0; i < pointers.size(); i++){
      visit(pointers[i]);
    }
  }
}


bool GarbageCollector::isMarked(Object* object){
  return map.count(object) == 1;
}
void GarbageCollector::freeResources(){
  std::cout << "free resources-elementos registrados:" <<createdObjects.size()<< std::endl;
  std::list<Object*>::iterator it;
  std::vector<Object*> vectorTem;
  for (it=createdObjects.begin(); it != createdObjects.end(); ++it){
    Object* object = *it;
    if(!isMarked(object)){
      std::cout << "Se va a eliminar" <<object<<"name:"<<object->getName()<< std::endl;
      std::string input = "Se eliminó el object:" + object->getName() + " .\n";
      reportFile << input;
      vectorTem.push_back(object);
    }
  }
  for (size_t i = 0; i < vectorTem.size(); i++) {
    createdObjects.remove(vectorTem[i]);
    delete(vectorTem[i]);
  }
}
void GarbageCollector::collect(){
  reportFile.open("Garbage_Collector_Report.txt",std::ofstream::out);
  visit(objectLobby);
  freeResources();
  reportFile.close();
}

void GarbageCollector::setObjectLobby(Object* object){
  objectLobby = object;
}


Object* GarbageCollector::cloneObject(Object* object){
  Object* newObject = object->clone();
  registerObject(newObject);
  return newObject;
}
