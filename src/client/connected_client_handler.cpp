#include "connected_client_handler.h"
#include <mutex>
#include "../common/lock.h"

ConnectedClientHandler::ConnectedClientHandler(ControladorEventos *cont_eventos): EventHandler(cont_eventos) {}

ConnectedClientHandler::~ConnectedClientHandler() {}

void ConnectedClientHandler::run(json j) {
	std::mutex mutex;
	Lock lock(mutex);
	std::cout << "Se conecta ok" << std::endl;
	cont_eventos->cliente_conectado();
}