#include "move_morph_handler.h"
#include "posicion.h"
#include <string>
#include <iostream>
#include <mutex>
#include "../common/lock.h"

MoveMorphHandler::MoveMorphHandler(ControladorEventos* cont_eventos): EventHandler(cont_eventos) {}

MoveMorphHandler::~MoveMorphHandler() {}

void MoveMorphHandler::run(json j) {
	std::mutex mutex;
	Lock lock(mutex);
	std::cout << "MoveMorphHandler" << std::endl;
	std::string morph = j["nombre"];
	double new_x = j["posicion"]["x"];
	double new_y = j["posicion"]["y"];
	Posicion new_pos(new_x, new_y);
	cont_eventos->cambiar_pos_morph(morph, &new_pos);
}