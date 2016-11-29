#include "connected_client_handler.h"

ConnectedClientHandler::ConnectedClientHandler
	(ClientHandler *client_handler) : EventHandler(client_handler) {}

ConnectedClientHandler::~ConnectedClientHandler() {}

void ConnectedClientHandler::handle(const json &j) const {
	client_handler->connected_client();
}
