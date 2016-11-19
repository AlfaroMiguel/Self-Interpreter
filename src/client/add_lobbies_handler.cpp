#include "add_lobbies_handler.h"

AddLobbiesHandler::AddLobbiesHandler(ClientHandler *client_handler): EventHandler(client_handler) {}

AddLobbiesHandler::~AddLobbiesHandler() {}

void AddLobbiesHandler::handle(json j) {
	std::string lobbies_str = j["lobbies"];
	json lobbies = json::parse((char*)lobbies_str.c_str());
	for (json::iterator it = lobbies.begin(); it != lobbies.end(); ++it) {
		std::string id = it.value();
		client_handler->set_lobby(id);
	}
	std::cout << "llama a iniciar" << std::endl;
	client_handler->iniciar();
}