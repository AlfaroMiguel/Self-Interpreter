#include "connected_client_handler.h"
#include "../common/lock.h"

#include <mutex>

ConnectedClientHandler::ConnectedClientHandler
	(ClientHandler *client_handler) : EventHandler(client_handler) {}

ConnectedClientHandler::~ConnectedClientHandler() {}

void ConnectedClientHandler::handle(json j) {
	client_handler->cliente_conectado();
}
