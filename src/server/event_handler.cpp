#include "event_handler.h"

EventHandler::EventHandler(ServerHandler* client_handler): server_handler(client_handler) {}

EventHandler::~EventHandler() {}

EventHandler::EventHandler(EventHandler&& otra){}

EventHandler& EventHandler::operator=(EventHandler&& otra){
    return *this;
}