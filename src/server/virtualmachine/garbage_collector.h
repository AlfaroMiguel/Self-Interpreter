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


  /*Se merca el objeto para que no se libere*/
  void markObject(Object *object);

  /*Se libera los objetos a los cuales ningun objeto tiene referencia*/
  void freeResources();
  /*Se verifica si el objeto esta marcado, es decir, si existe algun objeto que
  apunte a este.*/
  bool isMarked(Object* object);

  /*Se visita de ese objeto, es decir, se lo marcam y luego se visita sus slots*/
  void visit(Object* object);

  /*Se elimina aquellos objetos que fueron registrados mas de una vez*/
  void removeDuplicates();
  std::ofstream reportFile;
public:
  GarbageCollector(Object* lobbyPtr);
  ~GarbageCollector();

    /*Se visista todos los objetos que fueron registrados, y aquellos que
    ya no se encutren en el lobby, se lo libera */
    void collect();

    /*Se registra un objecto que existe en el modelo para luego poder ser
    liberado*/
    void registerObject(Object* object);

    /*Se setea el objectLobby al cual pertenece*/
    void setObjectLobby(Object* object);

    /*Crea un object del tipo Number con el valor del string*/
    Object* createNumber(std::string value);

    /*Crea un object del tipo SearcherObject con el nombre ingresado*/
    Object* createSearcherObject(std::string name);

    /*Crea un Object del tipo Expression generico*/
    Object* createExpression();

    /*Dado un objeto, devuelve un object que es copia de object*/
    Object* cloneObject(Object* object);
};
#endif
