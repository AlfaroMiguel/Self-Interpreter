#include "connected_client_handler.h"
#include "../common/lock.h"

#include <mutex>

ConnectedClientHandler::ConnectedClientHandler
	(ControladorEventos *cont_eventos) : EventHandler(cont_eventos) {}

ConnectedClientHandler::~ConnectedClientHandler() {}

void ConnectedClientHandler::handle(json j) {
	cont_eventos->cliente_conectado();
}
