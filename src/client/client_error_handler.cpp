#include "client_error_handler.h"

ClientErrorHandler::ClientErrorHandler(ClientHandler *client_handler) :
	EventHandler(client_handler) {}

ClientErrorHandler::~ClientErrorHandler() {}

void ClientErrorHandler::handle(const json &j) const {
	client_handler->client_connection_error();
}
