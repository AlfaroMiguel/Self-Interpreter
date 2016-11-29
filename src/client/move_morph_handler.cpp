#include "move_morph_handler.h"
#include "posicion.h"
#include <string>
#include <iostream>

#define JSON_ID_MORPH_ID "id"
#define JSON_ID_POSITION "posicion"
#define JSON_ID_X "x"
#define JSON_ID_Y "y"

MoveMorphHandler::MoveMorphHandler(ClientHandler *client_handler) :
	EventHandler(client_handler) {}

MoveMorphHandler::~MoveMorphHandler() {}

bool MoveMorphHandler::on_handle(const json &j) const {
	int morph_id = j[JSON_ID_MORPH_ID];
	double new_x = j[JSON_ID_POSITION][JSON_ID_X];
	double new_y = j[JSON_ID_POSITION][JSON_ID_Y];
	Posicion new_pos(new_x, new_y);
	client_handler->change_morph_position(morph_id, new_pos);
	return false;
}

void MoveMorphHandler::handle(const json &j) const {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this,
										  &MoveMorphHandler::on_handle), j));
}
