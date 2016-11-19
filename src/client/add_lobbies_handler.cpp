#include "add_lobbies_handler.h"

AddLobbiesHandler::AddLobbiesHandler(ControladorEventos *cont_eventos): EventHandler(cont_eventos) {}

AddLobbiesHandler::~AddLobbiesHandler() {}

void AddLobbiesHandler::handle(json j) {
	std::string lobbies_str = j["lobbies"];
	json lobbies = json::parse((char*)lobbies_str.c_str());
	for (json::iterator it = lobbies.begin(); it != lobbies.end(); ++it) {
		std::string id = it.value();
		cont_eventos->set_lobby(id);
	}
	std::cout << "llama a iniciar" << std::endl;
	cont_eventos->iniciar();
}