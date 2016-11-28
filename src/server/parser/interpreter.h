#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stack>
#include <map>

#include <string>
#include "../virtualmachine/object.h"
#include "../virtualmachine/garbage_collector.h"
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

  /*Se crea un numero con el el valor que se encuentre en el string*/
  void createNumber(const std::string value);

  /*Se crea una variable con un objeto del SearcherObject que luego buscar en su
  entorno a que tipo corresponde*/
  void createVariable(const std::string name);

  /*Se setea el nombre al objeto ultimo que se inserto en el stack*/
  void assignationExpression(const std::string name);

  /*Voy a tener algo expression addSlot algo, ese algo es un objectReference a la cual le
  le pido sus slots y los agreago a objectReference*/
  void addSlot(const std::string name);

  /*Todo lo que haya en el stack lo agrego como slot en un objectReference
  que lo agrego en el stack*/
  void encapsulateStack();

  /*Si no se encuetra en el map, lo creo y lo devuelvo*/
  Object* findExpression(const std::string name);

  /*Aca se crea una expression generica y se le setea el message, por eso se sabe que
   los 2 objetos que se encuentran son su receiver y argument*/
  void createExpression(const std::string message);

  /*Cuando se invoca un método de un objeto, se supone que este la cabeza del stack
  se setea la operacion que debe realizar y se pide que se evalue, luego se le pide
  el resultado para que muestre graficamente*/
  void sendMessage(const  std::string message);

  /*En caso de que me pidan redefinir un objeto, saco el objeto del stack que se
  supone que es el objeto al cual se mando el mensaje*/
  void setRepresentation(const  std::string value);

  /*Dado que se quiere clonar un objeto se lo busca en el lobby y se clona todos
  sus slots, tambien se guarda el estado isClone para luego guardarle el slot
  parent*/
  void cloneObject(const std::string id);

  /*Este método busca el objeto al cual se tiene que remover el slot, lo
  añade como un objeto que fue modificado, luego saca los slots del stack y va
  eliminando uno a uno los slots del objeto encontrado.*/
  void removeSlot(const std::string name);

  /*Este objeto saca todo lo que hay en el stack, esto se hace en caso de que haya
  un error de sintaxis, entonces el estado del stack es invalida porque hay objetos
  creados parcialmente*/
  void emptyStack();

  /*Se registra un objeto que no fue creado por medio de interpretar código
  como es el caso de la serializacion*/
  void registerObject(Object* object);

  GarbageCollector garbage;
  Object* lobbyObject;
  Object* entorno;
  Lobby* lobby;
  std::ofstream reportFile;
public:
    /*Se crea un interpreter y se carga todos los tipos de mensajes que puede llegar
    a recibir por parte de Parser*/
    Interpreter(Object* entorno_ptr, Lobby* lobby);
    /*Este el método que invoca Parser, acá se identifica cuál es el mensaje y se
    lo ejecuta*/
    void pushToken(const std::string id,const  std::string message,const std::string value);

    /*Este metodo es invocado por el server para que interprete un cadena*/
    void interpretChar(const char* buffer,Object* entorno_ptr);

    /*Se devuelve el vector con los objetos que fueron creados al interpretar
    el código Self interpretado en el método interpreterChar()*/
    std::vector<Object*> getCreatedObjets();

    /*Se devuelve el vector con los objetos que fueron modificados al interpretar
    el código Self interpretado en el método interpreterChar()*/
    std::vector<Object*> getModifiedObjets();



    /*Se vacia todos los vectores cada vez que interpreta una nueva cadena*/
    void clearVectors();

    /*Tiene que interpretar codigo de un archivo*/
    void interpretFile(const char* nameFile);


    /*Se registra todos los objetos que se encuentran en el lobby*/
    void registerObjects();
    ~Interpreter();
};

#endif /*INTERPRETER_H*/
