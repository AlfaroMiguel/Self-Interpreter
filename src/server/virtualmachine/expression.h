#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <string>
#include "nativevalue.h"
#include "searcher_object.h"

class Expression:public Object{
    Object* receiver;
    std::string operation;
    Object* argument;
    Object* result;
    bool create;
public:
    virtual void serialize(json& jserialization);
    static Expression* deserialize(json& jdeserialization, Lobby* lobby);

    Expression();
    ~Expression();

    /*Se setea el receiver y se le agrega el slot self*/
    void setReceiver(Object* receiverPtr);

    /*Se setea la operation que se va a ejecutar*/
    void setOperator(std::string operatorString);

    /*Se setea el argument y se le agrega el slot self*/
    void setArgument(Object* argumentPtr);
    void setResult(Object* resultPtr);
    std::vector<Object*> getReferences();

    bool createANewObject();

    /*Cuando se evalua expression, cada subexpression genera resultados
    parciales, para esto luego de evaluar, se lo setea a nullptr estos resultados
    de tal manera que recolector de basura lo recoga*/
    void deleteGarbage();


    /*De forma recursiva va pidiendo la representacion de sus componentes para
    devolver su representacion*/
    std::string getRepresentation() const ;

    /*Devuelve el NativeValue del result luego de evaluar la expression*/
    virtual NativeValue getValue();
    Object* getResult();

    /*Esto permite que se pueda acoplar mas mensaje a una expression que ya fue evaluada*/
    virtual NativeValue ejecute(std::string operationStr, Object* argumentPtr);

    /*Envia el mensaje a receiver con el argument seteado*/
    virtual void evaluate();

    /*Devuelve una copia de si mismo*/
    Object* clone() const;
    std::vector<Object*> getAtributs();

    virtual Object* searchForId(int objectId);
  };

#endif
