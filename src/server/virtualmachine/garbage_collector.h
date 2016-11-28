#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include "object.h"
#include <list>
#include <fstream>

class GarbageCollector{
private:
  std::list<Object*> createdObjects;
  Object* objectLobby;
  std::map<Object*,int> map;
  void markObject(Object *object);
  void freeResources();
  bool isMarked(Object* object);
  void visit(Object* object);
  void removeDuplicates();
  std::ofstream reportFile;
public:
  GarbageCollector(Object* lobbyPtr);
  ~GarbageCollector();
  void collect();
  void registerObject(Object* object);
  void setObjectLobby(Object* object);
  Object* createNumber(std::string value);
  Object* createSearcherObject(std::string name);
  Object* createExpression();
  Object* cloneObject(Object* object);
};
#endif
