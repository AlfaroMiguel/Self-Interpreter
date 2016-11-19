#include "client_error_handler.h"

ClientErrorHandler::ClientErrorHandler(ClientHandler *client_handler) :
	EventHandler(client_handler) {}

ClientErrorHandler::~ClientErrorHandler() {}

void ClientErrorHandler::handle(json j) {
	client_handler->error_ingreso_cliente();
}