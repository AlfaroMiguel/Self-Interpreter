#include "connect_client_handler.h"

#define JSONID "nombre"

ConnectClientHandler::ConnectClientHandler(ServerHandler* server_handler) :
EventHandler(server_handler){

}
ConnectClientHandler::~ConnectClientHandler(){}

void ConnectClientHandler::handle(json j){
    server_handler->connect(j[JSONID]);
}