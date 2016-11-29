#include "event_handler.h"

EventHandler::EventHandler(ClientHandler *client_handler) :
	client_handler(client_handler) {}

EventHandler::~EventHandler() {}