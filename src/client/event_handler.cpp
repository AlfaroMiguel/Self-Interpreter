#include "event_handler.h"

EventHandler::EventHandler(ControladorEventos* cont_eventos): cont_eventos(cont_eventos) {}

EventHandler::~EventHandler() {}

EventHandler::EventHandler(EventHandler&& otra){}

EventHandler& EventHandler::operator=(EventHandler&& otra){
	return *this;
}