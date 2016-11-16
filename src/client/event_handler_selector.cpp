#include "event_handler_selector.h"
#include "new_morph_handler.h"
#include "add_lobbies_handler.h"
#define EVENTO_CREAR "crear"
#define EVENTO_AGREGAR_LOBBIES "agregar lobbies"

EventHandlerSelector::EventHandlerSelector(ControladorEventos *cont_eventos) {
	event_handlers.insert(std::pair<std::string, EventHandler *>
		(EVENTO_CREAR, new NewMorphHandler(cont_eventos)));
	//event_handlers.insert(std::string, std::pair<EventHandler*>
	//	(EVENTO_AGREGAR_LOBBIES, new AddLobbiesHandler(cont_eventos)));
}

EventHandlerSelector::~EventHandlerSelector() {}

EventHandler *EventHandlerSelector::get_event_handler(const std::string &event) {
	return event_handlers.at(event);
}