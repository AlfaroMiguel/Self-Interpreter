#include "move_morph_client_handler.h"

#define MORPHID "id"
#define XID "x"
#define YID "y"

MoveMorphClientHandler::MoveMorphClientHandler(ServerHandler *server_handler) :
        EventHandler(server_handler) {
}

MoveMorphClientHandler::~MoveMorphClientHandler() {}

void MoveMorphClientHandler::handle(json j) {
    server_handler->moveMorph(j[MORPHID], j[XID], j[YID]);
}