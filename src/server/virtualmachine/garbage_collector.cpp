#include "garbage_collector.h"

#include "number.h"
#include "searcher_object.h"
#include "expression.h"
#include <iostream> //cout //stof

GarbageCollector::GarbageCollector(Object* lobbyPtr):objectLobby(lobbyPtr),reportFile("Garbage_Collector_LOG.txt"){
  reportFile << "==LOG==\n";
  reportFile.open("Garbage_Collector_LOG.txt",std::ofstream::app);
  registerObject(lobbyPtr);
  reportFile.close();
}



GarbageCollector::~GarbageCollector(){
  freeResources();
  reportFile.close();
}


void GarbageCollector::registerObject(Object* object){
  reportFile.open("Garbage_Collector_LOG.txt",std::ofstream::app);
  std::string report = "Se registró:" + object->getName() + "\n";
  reportFile << report;
  reportFile.close();
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
  reportFile.open("Garbage_Collector_LOG.txt",std::ofstream::app);
  if (object != nullptr){
    std::string report = "Object visit name:" + object->getName()+" " ;
    reportFile  << report;
    markObject(object);
    std::vector<Object*> pointers = object->getReferences();
    report = "cantidad de slots a visitar:" +std::to_string(pointers.size())+"\n";
    reportFile << report;
    for (size_t i = 0; i < pointers.size(); i++){
      std::cout << "nombre del slot:" <<pointers[i]->getName()<< std::endl;
      visit(pointers[i]);
    }
  }
  reportFile.close();
}


bool GarbageCollector::isMarked(Object* object){
  return map.count(object) == 1;
}
void GarbageCollector::freeResources(){
  reportFile.open("Garbage_Collector_LOG.txt",std::ofstream::app);
  reportFile << "free resources\n";
  std::list<Object*>::iterator it;
  std::vector<Object*> vectorTem;
  for (it=createdObjects.begin(); it != createdObjects.end(); ++it){
    Object* object = *it;
    if(!isMarked(object)){
      std::string input = "Se eliminó el object:" + object->getName() + " .\n";
      reportFile << input;
      vectorTem.push_back(object);
    }
  }
  for (size_t i = 0; i < vectorTem.size(); i++) {
    createdObjects.remove(vectorTem[i]);
    delete(vectorTem[i]);
  }
  reportFile.close();
}

void GarbageCollector::collect(){
  reportFile.open("Garbage_Collector_LOG.txt",std::ofstream::app);
  reportFile << "Cantidad de objetos registrados:"+ std::to_string(createdObjects.size())+ "\n";
  reportFile.close();
  visit(objectLobby);
  freeResources();
  map.clear();
}

void GarbageCollector::setObjectLobby(Object* object){
  objectLobby = object;
}


Object* GarbageCollector::cloneObject(Object* object){
  Object* newObject = object->clone();
  registerObject(newObject);
  return newObject;
}
