#include "client.h"

#include "lobby.h"

Client::Client(std::string clientName, ComunicadorCliente* clientReference) : clientName(clientName), clientReference(clientReference) {
    actualLobby = nullptr;
}

Client::~Client() {}

void Client::setActualLobby(Lobby *newActualLobby) {
    actualLobby = newActualLobby;
}

std::string Client::getClientName(){
    return clientName;
}