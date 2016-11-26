#include "lobby_data_handler.h"
#include <mutex>
#include "../common/lock.h"

LobbyDataHandler::LobbyDataHandler(ClientHandler *client_handler):EventHandler(client_handler) {}

LobbyDataHandler::~LobbyDataHandler() {}

void LobbyDataHandler::handle(const json& j) const{
	client_handler->open_lobby();
}