#include "initialize_client_handler.h"

#define JSONID "inicializar"

InitializeClientHandler::InitializeClientHandler(ServerHandler* server_handler) :
        EventHandler(server_handler){

}
InitializeClientHandler::~InitializeClientHandler(){}

void InitializeClientHandler::handle(json j){
    server_handler->initialize();
}