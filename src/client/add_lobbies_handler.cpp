#include "add_lobbies_handler.h"

#define JSON_ID_LOBBIES "lobbies"

AddLobbiesHandler::AddLobbiesHandler(ClientHandler *client_handler) :
	EventHandler(client_handler) {}

AddLobbiesHandler::~AddLobbiesHandler() {}

void AddLobbiesHandler::handle(const json &j) const {
	std::string lobbies_str = j[JSON_ID_LOBBIES];
	json lobbies = json::parse((char *) lobbies_str.c_str());
	for (json::iterator it = lobbies.begin(); it != lobbies.end(); ++it) {
		std::string lobby_id = it.value();
		client_handler->add_lobby(lobby_id);
	}
	client_handler->set_lobbies();
}
