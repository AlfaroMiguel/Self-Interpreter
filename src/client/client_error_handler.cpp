#include "client_error_handler.h"
#include <mutex>
#include "../common/lock.h"
ClientErrorHandler::ClientErrorHandler(ControladorEventos *cont_eventos): EventHandler(cont_eventos) {}

ClientErrorHandler::~ClientErrorHandler() {}

void ClientErrorHandler::run(json j) {
	std::mutex mutex;
	Lock lock(mutex);
	std::cout << "Ingresa a error" << std::endl;
	cont_eventos->error_ingreso_cliente();
}