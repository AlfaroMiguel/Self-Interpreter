#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>
#include <map>

#include <string>
#include "../object.h"

class Lobby;

class Interpreter{
private:
  std::map<std::string,int> mapMessages;
  std::stack<Object*> stack;
  std::map<std::string,Object*> map;
  void createNumber(std::string value);
  void createVariable(std::string name);
  void assignationExpression(std::string name);
  void addSlot(std::string name);
  void encapsulateStack();
  Object* findExpression(std::string name);
  void createExpression(std::string message);
  void sendMessage(std::string message);
  Object* entorno;
    Lobby* lobby;
public:
    Interpreter(Object* entorno_ptr, Lobby* lobby);
    Interpreter();
    void pushToken(std::string id,std::string message,std::string value);
    void interpretChar(char* buffer);
    void interpretFile(const char* nameFile);
    void end();
    ~Interpreter();

    void initializeMorphs(Lobby* lobbyContainer);
    void moveMorph(std::string morphName, double newX, double newY);
};

#endif /*INTERPRETER_H*/
