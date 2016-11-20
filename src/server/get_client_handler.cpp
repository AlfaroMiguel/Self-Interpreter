#include "get_client_handler.h"

#define CODEID "codigo"

GetClientHandler::GetClientHandler(ServerHandler* server_handler) :
        EventHandler(server_handler){

}
GetClientHandler::~GetClientHandler(){}

void GetClientHandler::handle(json j){
    server_handler->interpretSelfGet(j[CODEID]);
}