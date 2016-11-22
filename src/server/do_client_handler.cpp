#include "do_client_handler.h"

#define CODEID "codigo"

DoClientHandler::DoClientHandler(ServerHandler* server_handler) :
        EventHandler(server_handler){

}
DoClientHandler::~DoClientHandler(){}

void DoClientHandler::handle(json j){
    server_handler->interpretSelfDo(j[CODEID]);
}