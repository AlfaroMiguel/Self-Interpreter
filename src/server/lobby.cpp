#include "lobby.h"
#include "parser/interpreter.h"
#include "iostream"
Lobby::Lobby(std::string lobbyName, bool isShared, Object* lobbyReference) :
lobbyName(lobbyName), isShared(isShared), lobbyReference(lobbyReference){
    interpreter = new Interpreter(lobbyReference, this);
}

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
    auto itClient = clientsConnected.find((client->getClientName()));
    if(itClient == clientsConnected.end())
        clientsConnected.insert(std::make_pair(client->getClientName(), client));
    else
        itClient->second = client;

}

void Lobby::disconnectClient(Client* client){
    auto itClient = clientsConnected.find(client->getClientName());
    if(itClient != clientsConnected.end())
        itClient->second = nullptr;
}

void Lobby::notifyClient(std::string eventName, std::string clientName, Morph& morph){
    std::cout << "Empieza a notificar"<< std::endl;
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end())
        if(itClient->second != nullptr)
            itClient->second->notify(eventName, morph);
}

void Lobby::notifyClients(std::string eventName, Morph& morph){
    std::cout << "Empieza a notificar"<< std::endl;

    for(auto itClient = clientsConnected.begin(); itClient != clientsConnected.end(); itClient++){
        std::cout << "Entra a iterar los clientes" << std::endl;
        if(itClient->second != nullptr){
            itClient->second->notify(eventName, morph);
        }
    }
    std::cout << "Termina de notificar" << std::endl;
}

void Lobby::initializeClient(std::string clientName) {
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end())
        if(itClient->second != nullptr)
            interpreter->initializeMorphs(this);

}

void Lobby::moveMorph(std::string morphName, double newX, double newY){
    interpreter->moveMorph(morphName, newX, newY);
}