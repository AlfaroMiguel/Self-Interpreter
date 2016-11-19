#include "lobby.h"
#include "parser/interpreter.h"
#include "iostream"
Lobby::Lobby(std::string lobbyName, bool isShared, Object* lobbyReference) :
lobbyName(lobbyName), isShared(isShared), lobbyReference(lobbyReference){
    interpreter = new Interpreter(lobbyReference, this);
    std::string shellCode = "lobby _AddSlots: (| shell = (|  |).  |)."; //Ni bien se crea un interpreter le agrego la shell al lobby
    this->interpretCodeGet(shellCode);
}

Lobby::~Lobby() {}

std::string Lobby::getLobbyName(){
    return lobbyName;
}

bool Lobby::clientConnected(std::string clientName){
    auto it = this->clientsConnected.find(clientName);
    return (it != clientsConnected.end());
}

bool Lobby::clientConnected(Client* client){
    return clientConnected(client->getClientName());
}

bool Lobby::isLobbyShared(){
    return isShared;
}

void Lobby::connectClient(Client* client){
    std::cout << "Conecto client: " << client->getClientName() << " al lobby: " << this->lobbyName << std::endl;
    auto itClient = clientsConnected.find((client->getClientName()));
    if(itClient == clientsConnected.end())
        clientsConnected.insert(std::make_pair(client->getClientName(), client));
    else
        itClient->second = client;
}

void Lobby::disconnectClient(Client* client){
    std::cout << "Desconecto del lobby a " << client->getClientName() << std::endl;
    auto itClient = clientsConnected.find(client->getClientName());
    if(itClient != clientsConnected.end())
        itClient->second = nullptr;
}

void Lobby::notifyClient(std::string eventName, std::string clientName, Morph& morph){
    std::cout << "Empieza a notificar (notifyClient)"<< std::endl;
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end())
        if(itClient->second != nullptr)
            itClient->second->notify(eventName, morph);
}

void Lobby::notifyClients(std::string eventName, Morph& morph, std::string clientNameUnnotified = ""){
    std::cout << "Empieza a notificar (notifyClients)"<< std::endl;

    for(auto itClient = clientsConnected.begin(); itClient != clientsConnected.end(); itClient++){
        std::cout << "Entra a iterar los clientes" << std::endl;
        std::cout << clientsConnected.size() << std::endl;
        if(itClient->second != nullptr){
            if(itClient->second->getClientName() != clientNameUnnotified)
                itClient->second->notify(eventName, morph);
        }
    }
    std::cout << "Termina de notificar" << std::endl;
}

void Lobby::initializeClient(std::string clientName) {
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end())
        if(itClient->second != nullptr)
            this->initializeMorphs();

}

void Lobby::moveMorph(std::string clientName, int morphId, double newX, double newY){
    auto itObject = visibleObjects.find(morphId);
    if (itObject == visibleObjects.end()){
        std::cout << "No encontre el morph" << morphId << std::endl;
        return;
    }
    std::cout << "Encontre el morph" << morphId << std::endl;
    Object *object = itObject->second;
    object->moveMorph(clientName, newX, newY);
}

void Lobby::interpretCodeGet(std::string code){
    std::cout << "Soy el lobby: " << lobbyName << " me llego Get con el codigo: " << code << std::endl;
    std::vector<Object*> objectsCreated  = interpreter->interpretChar(code.c_str());
    for(auto itObject = objectsCreated.begin(); itObject != objectsCreated.end(); itObject++){
        std::cout << "En esta interpretacion se creo: " << (*itObject)->getName() << std::endl;
        visibleObjects.insert(std::make_pair((*itObject)->getMorphId(), *itObject));
        (*itObject)->notifyClients("crear");
    }
}

void Lobby::interpretCodeDo(std::string code){
    std::cout << "Soy el lobby: " << lobbyName << " me llego Do con el codigo: " << code << std::endl;
    interpreter->interpretChar((code.c_str()));
}


void Lobby::initializeMorphs() {
    std::cout << "Initialize Morphs" << std::endl;
    for (auto itObject = visibleObjects.begin(); itObject != visibleObjects.end(); itObject++) {
        std::cout << "Notifica: " << itObject->second->getName() << std::endl;
        itObject->second->notifyClients("crear");
    }
}
