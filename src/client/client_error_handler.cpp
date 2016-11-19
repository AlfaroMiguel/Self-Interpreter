#include "client_error_handler.h"
#include "../common/lock.h"

#include <mutex>

ClientErrorHandler::ClientErrorHandler(ControladorEventos *cont_eventos) :
	EventHandler(cont_eventos) {}

ClientErrorHandler::~ClientErrorHandler() {}

void ClientErrorHandler::handle(json j) {
//	std::mutex mutex;
//	Lock lock(mutex);
	cont_eventos->error_ingreso_cliente();
}