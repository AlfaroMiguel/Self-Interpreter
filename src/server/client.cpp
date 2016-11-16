#include "client.h"

#include "morph.h"
#include "lobby.h"
#include "comunicador_cliente.h"

Client::Client(std::string clientName, ComunicadorCliente* clientReference) : clientName(clientName), clientReference(clientReference) {
    actualLobby = nullptr;
}

Client::~Client() {}

void Client::setActualLobby(Lobby *newActualLobby) {
    actualLobby = newActualLobby;
    std::cout << "entre aca" << std::endl;
    actualLobby->initializeClient(clientName);
}

Lobby* Client::getActualLobby(){
    return actualLobby;
}

std::string Client::getClientName(){
    return clientName;
}

void Client::notify(std::string eventName, Morph& morph){
    std::string event = morph.getEvent(eventName); //Hardcodeo por ahora
    clientReference->enviarEvento(event);
}