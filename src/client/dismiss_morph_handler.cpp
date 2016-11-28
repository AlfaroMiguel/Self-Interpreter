#include "dismiss_morph_handler.h"

DismissMorphHandler::DismissMorphHandler
	(ClientHandler *client_handler) : EventHandler(client_handler) {}

DismissMorphHandler::~DismissMorphHandler() {}

void DismissMorphHandler::handle(const json& j) const{
	int id = j["id"];
	client_handler->dismiss_morph(id);
}