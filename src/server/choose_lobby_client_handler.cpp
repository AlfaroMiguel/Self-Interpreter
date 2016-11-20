#include "choose_lobby_client_handler.h"

#define LOBBYID "lobby"
#define STATELOBBYID "estado"

ChooseLobbyClientHandler::ChooseLobbyClientHandler(ServerHandler* server_handler) :
        EventHandler(server_handler){
}

ChooseLobbyClientHandler::~ChooseLobbyClientHandler(){}

void ChooseLobbyClientHandler::handle(json j){
    server_handler->chooseLobby(j[LOBBYID], j[STATELOBBYID]);
}