#include "morph.h"
#include "../../common/json.hpp"
using json = nlohmann::json;

int Morph::idNumber = 0;

Morph::Morph() {
    x = 0.0;
    y = 0.0;
}

Morph::~Morph() {}

void Morph::setName(const std::string &newName) {
    name = newName;
    id = idNumber++;
}

void Morph::changeName(const std::string &newName){
    name = newName;
}

void Morph::changePosition(double newX, double newY) {
    x = newX;
    y = newY;
}

void Morph::addSlot(const std::string& nombre, const std::string& valor) {
    auto itSlot = slots.find(nombre);
    if(itSlot == slots.end())
        slots.insert(std::make_pair(nombre, valor));

    else
        itSlot->second = valor;
}

void Morph::removeSlot(const std::string& nombre){
    auto itSlot = slots.find(nombre);
    if(itSlot != slots.end()) slots.erase(nombre);
}

std::string Morph::getEvent(const std::string& eventName){
    json eventj;
    eventj["evento"] = eventName;
    eventj["nombre"] = name;
    eventj["id"] = id;
    eventj["posicion"]["x"] = x;
    eventj["posicion"]["y"] = y;
    json slotsj;
    for(auto itSlot = slots.begin(); itSlot != slots.end(); itSlot++){
        slotsj[itSlot->first] = itSlot->second;
    }
    eventj["slots"] = slotsj.dump();

    //TEST LINEA
    eventj["unionName"] = unionName;
    eventj["unionID"] = unionID;

    return eventj.dump();
}

int Morph::getId(){
    return id;
}

void Morph::decreaseID(){
    idNumber--;
}

/*Serializacion*/

void Morph::serialize(json& jserialization){
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

void Morph::deserialize(json& jdeserialization){
    this->setName(jdeserialization["name"]);
    this->changePosition(jdeserialization["x"], jdeserialization["y"]);
    json jSlots = jdeserialization["slots"];
    for(auto itSLots = jSlots.begin(); itSLots != jSlots.end(); itSLots++){
        this->addSlot(itSLots.key(), itSLots.value());
    }
    this->id = jdeserialization["id"];
}