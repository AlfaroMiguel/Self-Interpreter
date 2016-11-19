#include "client_error_handler.h"
#include "../common/lock.h"

#include <mutex>

ClientErrorHandler::ClientErrorHandler(ClientHandler *client_handler) :
	EventHandler(client_handler) {}

ClientErrorHandler::~ClientErrorHandler() {}

void ClientErrorHandler::handle(json j) {
//	std::mutex mutex;
//	Lock lock(mutex);
	client_handler->error_ingreso_cliente();
}