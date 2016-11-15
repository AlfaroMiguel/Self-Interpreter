#include "lobby.h"

Lobby::Lobby(std::string lobbyName, bool isShared, Object* lobbyReference) :
lobbyName(lobbyName), isShared(isShared), lobbyReference(lobbyReference){}

Lobby::~Lobby() {}

std::string Lobby::getLobbyName(){
    return lobbyName;
}

bool Lobby::clientConnected(std::string clientName){
    auto it = this->clientsConnected.find(clientName);
    return !(it == clientsConnected.end());
}

bool Lobby::clientConnected(Client* client){
    return clientConnected(client->getClientName());
}

bool Lobby::isLobbyShared(){
    return isShared;
}

void Lobby::connectClient(Client* client){
    clientsConnected.insert(std::make_pair(client->getClientName(), client));
}

void Lobby::disconnectClient(Client* client){
    clientsConnected.erase(client->getClientName());
}