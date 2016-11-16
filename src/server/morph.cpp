#include "morph.h"
#include "../common/json.hpp"
using json = nlohmann::json;

Morph::Morph() {
    x = 0.0; //Chequear posiciones
    y = 0.0;
}

Morph::~Morph() {}

void Morph::setName(const std::string &newName) {
    name = newName;
}

void Morph::changePosition(double newX, double newY) {
    std::cout << "Cambio a nueva posicion x = " << newX << " y = " << newY << std::endl;
    x = newX;
    y = newY;
}

void Morph::addSlot(std::string nombre, std::string valor) {
    auto itSlot = slots.find(nombre);
    if(itSlot == slots.end())
        slots.insert(std::make_pair(nombre, valor));

    else
        itSlot->second = valor;
}

std::string Morph::getEvent(std::string eventName){
    json eventj;
    eventj["evento"] = eventName;
    eventj["nombre"] = name;
    eventj["posicion"]["x"] = x;
    eventj["posicion"]["y"] = y;
    json slotsj;
    for(auto itSlot = slots.begin(); itSlot != slots.end(); itSlot++){
        slotsj[itSlot->first] = itSlot->second;
    }
    eventj["slots"] = slotsj.dump();
    return eventj.dump();
}