#include "add_lobbies_handler.h"
#include <string>
#include <mutex>
#include "../common/lock.h"
AddLobbiesHandler::AddLobbiesHandler(ControladorEventos* cont_eventos): EventHandler(cont_eventos) {}

AddLobbiesHandler::~AddLobbiesHandler() {}

void AddLobbiesHandler::run(json j) {
	std::mutex mutex;
	Lock lock(mutex);
	std::string lobbies_str = j["lobbies"];
	json lobbies = json::parse((char*)lobbies_str.c_str());
	for (json::iterator it = lobbies.begin(); it != lobbies.end(); ++it) {
		std::string id = it.value();
		cont_eventos->set_lobby(id);
	}
	cont_eventos->iniciar();
}