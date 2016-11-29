#include "dismiss_morph_handler.h"

#define JSON_ID_MORPH_ID "id"

DismissMorphHandler::DismissMorphHandler
	(ClientHandler *client_handler) : EventHandler(client_handler) {}

DismissMorphHandler::~DismissMorphHandler() {}

void DismissMorphHandler::handle(const json &j) const {
	int morph_id = j[JSON_ID_MORPH_ID];
	client_handler->dismiss_morph(morph_id);
}