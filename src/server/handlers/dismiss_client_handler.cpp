#include "dismiss_client_handler.h"

#define MORPHID "id"

DismissClientHandler::DismissClientHandler(ServerHandler* server_handler) :
        EventHandler(server_handler){
}

DismissClientHandler::~DismissClientHandler(){}

void DismissClientHandler::handle(json j){
    server_handler->dismissMorph(j[MORPHID]);
}