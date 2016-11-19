#include "move_morph_handler.h"
#include "posicion.h"
#include <string>
#include <iostream>
#include <mutex>
#include "../common/lock.h"

MoveMorphHandler::MoveMorphHandler(ClientHandler* client_handler): EventHandler(client_handler) {}

MoveMorphHandler::~MoveMorphHandler() {}

bool MoveMorphHandler::on_handle(json j){
	std::string morph = j["nombre"];
	double new_x = j["posicion"]["x"];
	double new_y = j["posicion"]["y"];
	Posicion new_pos(new_x, new_y);
	client_handler->cambiar_pos_morph(morph, &new_pos);
	return false;
}

void MoveMorphHandler::handle(json j) {
//	std::mutex mutex;
//	Lock lock(mutex);
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &MoveMorphHandler::on_handle), j));
//	std::cout << "MoveMorphHandler" << std::endl;
//	std::string morph = j["nombre"];
//	double new_x = j["posicion"]["x"];
//	double new_y = j["posicion"]["y"];
//	std::cout << "Recibi posicion: " << new_x << ", " << new_y << std::endl;
//	Posicion new_pos(new_x, new_y);
//	client_handler->cambiar_pos_morph(morph, &new_pos);
}
