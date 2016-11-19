#include "lobby_data_handler.h"
#include <mutex>
#include "../common/lock.h"

LobbyDataHandler::LobbyDataHandler(ControladorEventos *cont_eventos):EventHandler(cont_eventos) {}

LobbyDataHandler::~LobbyDataHandler() {}

void LobbyDataHandler::handle(json j) {
//	std::mutex mutex;
//	Lock lock(mutex);
	//tiene que crear la vm con todos los morphs
	cont_eventos->crear_vm();
}