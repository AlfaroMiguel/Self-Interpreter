#include "morph.h"
#include "../../common/json.hpp"
using json = nlohmann::json;

int Morph::idNumber = 0;

Morph::Morph() {
    x = 0.0; //Chequear posiciones
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
    std::cout << "Cambio a nueva posicion x = " << newX << " y = " << newY << std::endl;
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
    return eventj.dump();
}

int Morph::getId(){
    return id;
}