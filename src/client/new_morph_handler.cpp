#include "new_morph_handler.h"
#include <string>
#include <map>
NewMorphHandler::NewMorphHandler(ControladorEventos* cont_eventos): EventHandler(cont_eventos) {}

NewMorphHandler::~NewMorphHandler() {}

void NewMorphHandler::run(json j) {
	std::map<std::string, std::string> dic_slots;
	std::string nombre = j["nombre"];
	double x = j["posicion"]["x"];
	double y = j["posicion"]["y"];
	std::string slots_str = j["slots"];
	json slots = json::parse((char*)slots_str.c_str());
	for (json::iterator it = slots.begin(); it != slots.end(); ++it) {
		std::string nombre = it.key();
		std::string valor = it.value();
		dic_slots.insert(std::make_pair(nombre, valor));
	}
	cont_eventos->crear_morph(nombre, x, y, dic_slots);
}