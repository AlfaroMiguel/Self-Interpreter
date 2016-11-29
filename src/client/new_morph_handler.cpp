#include "new_morph_handler.h"
#include <string>
#include <map>

#define JSON_ID_MORPH_ID "id"
#define JSON_ID_POSITION "posicion"
#define JSON_ID_X "x"
#define JSON_ID_Y "y"
#define JSON_ID_NAME "nombre"
#define JSON_ID_UNION_ID "unionID"
#define JSON_ID_UNION_NAME "unionName"
#define JSON_ID_SLOTS "slots"
NewMorphHandler::NewMorphHandler(ClientHandler* client_handler): EventHandler(client_handler) {}

NewMorphHandler::~NewMorphHandler() {}

void NewMorphHandler::handle(const json& j) const{
	std::map<std::string, std::string> slots_map;
	std::string name = j[JSON_ID_NAME];
	int id = j[JSON_ID_MORPH_ID];
	double x = j[JSON_ID_POSITION][JSON_ID_X];
	double y = j[JSON_ID_POSITION][JSON_ID_Y];
	int parent_id = j[JSON_ID_UNION_ID];
	std::string slot_name = j[JSON_ID_UNION_NAME];
	std::string slots_str = j[JSON_ID_SLOTS];
	json slots = json::parse((char*)slots_str.c_str());
	for (json::iterator it = slots.begin(); it != slots.end(); ++it) {
		std::string name = it.key();
		std::string value = it.value();
		slots_map.insert(std::make_pair(name, value));
	}
	Posicion morph_pos(x, y);
	client_handler->create_morph(name, morph_pos, slots_map, id, parent_id, slot_name);
}