#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef MORPH_H
#define MORPH_H

#include <string>
#include <map>

/*Clase que representa un Morph del cliente contiene toda la informacion
 * necesaria para poder representarlo correctamente
 * Nombre del morph
 * Posicion x del morph
 * Posicion y del morph
 * Map con slots que es representado como <nombre, representacion>
 * Un id que lo hace unico y se identifica por este numero*/
class Morph{
private:
    std::string name;
    double x;
    double y;
    std::map<std::string, std::string> slots;
    int id;
public:

    //Serialization TEST

    void serialize(json& jserialization){
        jserialization["name"] = name;
        jserialization["x"] = x;
        jserialization["y"] = y;

        json jSlots;
        for(auto itSlot = slots.begin(); itSlot != slots.end(); itSlot++){
            jSlots.push_back(std::make_pair(itSlot->first, itSlot->second));
        }
        jserialization["slots"] = jSlots;
        jserialization["id"] = id;
    }

    void deserialize(json& jdeserialization){
        this->setName(jdeserialization["name"]);
        this->changePosition(jdeserialization["x"], jdeserialization["y"]);
        json jSlots = jdeserialization["slots"];
        for(auto itSLots = jSlots.begin(); itSLots != jSlots.end(); itSLots++){
            this->addSlot(itSLots.key(), itSLots.value());
        }
        this->id = jdeserialization["id"];
    }

    static int idNumber;
    /*Crea un morph, se le setea un unico id*/
    Morph();
    /*Destructor del morph*/
    ~Morph();
    /*Recibe un nombre y le setea el nombre al morph*/
    void setName(const std::string& newName);
    void changeName(const std::string& newName);
    /*Recibe dos nuevas posiciones y se le cambia la posicion al morph*/
    void changePosition(double newX, double newY);
    /*Recibe dos cadenas, una siendo el nombre del slot a agregar y la otra
     * la represetnacion del valor del slot, se agrega al morph*/
    void addSlot(const std::string& nombre,const std::string& valor);
    /*Recibe el nombre de un slot y lo remueve del Morph*/
    void removeSlot(const std::string& nombre);
    /*Obtiene la representacion para notificarle al cliente en el protocolo establecido*/
    std::string getEvent(const std::string &eventName);
    /*Devuelve el id del morph*/
    int getId();
};

#endif