#ifndef NUMBER_H
#define NUMBER_H

#include "expression.h"
#include "nativevalue.h"
#include "object.h"
#include <map>


class Number : public Object{
private:
  std::string operation;
  NativeValue value;
public:

    //Metodo para serializar el objeto number
    void serialize(json& jserialization);

    //Metodo estatico para deserializar el objeto Number
    static Number* deserialize(json& jdeserialization, Lobby* lobby);
    Number();


    /*Esto modela un numero entero dentro de los objetos de self*/
    Number(int valueAux);
    ~Number();

    /*Devuelve el NativeValue que contiene como atributo*/
    NativeValue convertToNativeValue();

    /*Se setea el valor que contiene*/
    void setValue(int valueAux);

    /*Devuelve al igual que el convertToNativeValue() el NativeValue*/
    NativeValue getValue();
    /*Se setea el mensaje que desea realizar al numero */
    void setOperator(std::string operatorString);

    /*Se ejecuta la operation con los argumento que se pasan en expression*/
    NativeValue ejecute(std::string operation, Object* expression);

    /*Devuelve una copia de si mismo*/
    Object* clone();
    /*Devuelve el resulta de la operacion de que se realizo en ejecute()*/
    Object* getResult();
};

#endif
