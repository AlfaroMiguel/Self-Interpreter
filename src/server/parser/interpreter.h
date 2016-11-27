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
  void createNumber(const std::string value);
  void createVariable(const std::string name);
  void assignationExpression(const std::string name);
  void addSlot(const std::string name);
  void encapsulateStack();
  Object* findExpression(const std::string name);
  void createExpression(const std::string message);
  void sendMessage(const  std::string message);
  void setRepresentation(const  std::string value);
  void cloneObject(const std::string id);
  void removeSlot(const std::string name);
  void emptyStack();

  GarbageCollector garbage;
  Object* lobbyObject;
  Object* entorno;
  Lobby* lobby;
  std::ofstream reportFile;
public:
    Interpreter(Object* entorno_ptr, Lobby* lobby);
    void pushToken(const std::string id,const  std::string message,const std::string value);
    void interpretChar(const char* buffer,Object* entorno_ptr);
    std::vector<Object*> getCreatedObjets();
    std::vector<Object*> getModifiedObjets();
    void clearVectors();
    void interpretFile(const char* nameFile);
    ~Interpreter();
};

#endif /*INTERPRETER_H*/
