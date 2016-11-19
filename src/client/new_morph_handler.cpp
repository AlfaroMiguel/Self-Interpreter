#include "new_morph_handler.h"
#include <string>
#include <map>
NewMorphHandler::NewMorphHandler(ClientHandler* client_handler): EventHandler(client_handler) {}

NewMorphHandler::~NewMorphHandler() {}

void NewMorphHandler::handle(json j) {
	std::map<std::string, std::string> dic_slots;
	std::string nombre = j["nombre"];
	int id = j["id"];
	double x = j["posicion"]["x"];
	double y = j["posicion"]["y"];
	std::string slots_str = j["slots"];
	json slots = json::parse((char*)slots_str.c_str());
	for (json::iterator it = slots.begin(); it != slots.end(); ++it) {
		std::string nombre = it.key();
		std::string valor = it.value();
		dic_slots.insert(std::make_pair(nombre, valor));
	}
	Posicion pos_morph(x, y);
	client_handler->crear_morph(nombre, pos_morph, dic_slots, id);
}