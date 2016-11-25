#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>
#include <map>

#include <string>
#include "../object.h"
#include "../garbage_collector.h"
#include <fstream>

class Lobby;

class Interpreter{
private:
  bool isClone;
  Object* parentClone;
  std::map<std::string,int> mapMessages;
  std::stack<Object*> stack;
  std::map<std::string,Object*> map;
  std::vector<Object*> createdObjects;
  std::vector<Object*> modifiedObjects;
  void createNumber(std::string value);
  void createVariable(std::string name);
  void assignationExpression(std::string name);
  void addSlot(std::string name);
  void encapsulateStack();
  Object* findExpression(std::string name);
  void createExpression(std::string message);
  void sendMessage(std::string message);
  void setRepresentation(std::string value);
  void cloneObject(std::string id);
  void removeSlot(std::string name);
  void clearVectors();
  GarbageCollector garbage;
  Object* entorno;
  Lobby* lobby;
  std::ofstream reportFile;
public:
    Interpreter(Object* entorno_ptr, Lobby* lobby);
    void pushToken(std::string id,std::string message,std::string value);
    void interpretChar(const char* buffer);
    std::vector<Object*> getCreatedObjets();
    std::vector<Object*> getModifiedObjets();
    void interpretFile(const char* nameFile);
    ~Interpreter();

};

#endif /*INTERPRETER_H*/
