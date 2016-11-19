#include "move_morph_handler.h"
#include "posicion.h"
#include <string>
#include <iostream>
#include <mutex>
#include "../common/lock.h"

MoveMorphHandler::MoveMorphHandler(ClientHandler* client_handler): EventHandler(client_handler) {}

MoveMorphHandler::~MoveMorphHandler() {}

bool MoveMorphHandler::on_handle(json j){
	int morph_id = j["id"];
	double new_x = j["posicion"]["x"];
	double new_y = j["posicion"]["y"];
	Posicion new_pos(new_x, new_y);
	client_handler->cambiar_pos_morph(morph_id, &new_pos);
	return false;
}

void MoveMorphHandler::handle(json j) {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &MoveMorphHandler::on_handle), j));
}
