#include "event_handler_selector.h"
#include "new_morph_handler.h"
#include "add_lobbies_handler.h"
#include "connected_client_handler.h"
#include "client_error_handler.h"
#include "lobby_data_handler.h"
#include "move_morph_handler.h"
#include "dismiss_morph_handler.h"
#include <string>

#define EVENTO_CREAR "crear"
#define EVENTO_AGREGAR_LOBBIES "agregar lobbies"
#define EVENTO_CLIENTE_CONECTADO "cliente conectado"
#define EVENTO_ERROR_CLIENTE "error"
#define EVENTO_DATOS_LOBBY "datos lobby"
#define EVENTO_MOVER "mover morph"
#define EVENTO_DISMISS "dismiss"

EventHandlerSelector::EventHandlerSelector(ClientHandler *client_handler) {
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_CREAR,
							   new NewMorphHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_AGREGAR_LOBBIES,
							   new AddLobbiesHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_CLIENTE_CONECTADO,
							   new ConnectedClientHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_ERROR_CLIENTE,
							   new ClientErrorHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_DATOS_LOBBY,
							   new LobbyDataHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_MOVER,
							   new MoveMorphHandler(client_handler)));
	event_handlers.insert(std::pair<std::string, EventHandler *>
							  (EVENTO_DISMISS,
							   new DismissMorphHandler(client_handler)));
}

EventHandlerSelector::~EventHandlerSelector() {}

EventHandler* EventHandlerSelector::get_event_handler(const std::string &event) {
	return event_handlers.at(event);
}