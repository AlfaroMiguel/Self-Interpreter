#include "change_name_client_handler.h"

#define OBJECTID "id"
#define NEWNAME "new name"

ChangeNameClientHandler::ChangeNameClientHandler(ServerHandler *server_handler) :
        EventHandler(server_handler) {
}

ChangeNameClientHandler::~ChangeNameClientHandler() {}

void ChangeNameClientHandler::handle(json j) {
    server_handler->changeObjectName(j[OBJECTID], j[NEWNAME]);
}