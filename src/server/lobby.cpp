#include "lobby.h"
#include "parser/interpreter.h"
#include "iostream"

Lobby::Lobby(){}

Lobby::Lobby(const std::string& lobbyName, bool isShared, Object* lobbyReference) :
lobbyName(lobbyName), isShared(isShared), lobbyReference(lobbyReference){
    interpreter = new Interpreter(lobbyReference, this);
    std::string shellCode = "lobby _AddSlots: (| shell = (|  |).  |)."; //Ni bien se crea un interpreter le agrego la shell al lobby
    this->interpretCodeGet(shellCode);
}

Lobby::~Lobby() {}

std::string Lobby::getLobbyName(){
    return lobbyName;
}

bool Lobby::clientConnected(const std::string& clientName){
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
    std::cout << "El cliente: " << client->getClientName() << " se conecto al lobby: " << this->lobbyName << std::endl;
    auto itClient = clientsConnected.find((client->getClientName()));
    if(itClient == clientsConnected.end())
        clientsConnected.insert(std::make_pair(client->getClientName(), client));
    else {
        std::cout << "Lobby::connectClient : no encontre el cliente" << std::endl;
        itClient->second = client;
    }
}

void Lobby::disconnectClient(Client* client){
    std::cout << "Se desconecto del lobby a " << client->getClientName() << std::endl;
    auto itClient = clientsConnected.find(client->getClientName());
    if(itClient != clientsConnected.end())
        itClient->second = nullptr;
}

void Lobby::notifyClient(const std::string& eventName, const std::string& clientName, Morph& morph){
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end())
        if(itClient->second != nullptr)
            itClient->second->notify(eventName, morph);
}

void Lobby::notifyClients(const std::string& eventName, Morph& morph, const std::string& clientNameUnnotified = ""){
    for(auto itClient = clientsConnected.begin(); itClient != clientsConnected.end(); itClient++){
        std::cout << clientsConnected.size() << std::endl;
        if(itClient->second != nullptr){
            if(itClient->second->getClientName() != clientNameUnnotified)
                itClient->second->notify(eventName, morph);
        }
    }
}

void Lobby::initializeClient(const std::string& clientName) {
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end()) {
        if (itClient->second != nullptr) {
            this->initializeMorphs();
        }
    }
    std::cout << "Termino Lobby::initializeClient" << std::endl;
}

void Lobby::moveMorph(const std::string& clientName, int morphId, double newX, double newY){
    auto itObjectID = visibleObjects.find(morphId);
    if (itObjectID == visibleObjects.end())return;
    std::cout << "Lobby:moveMorph: busco object" << std::endl;
    if(lobbyReference == nullptr) std::cout << "Lobby:moveMorph: lobbyReference es null " << morphId << std::endl;
    Object *object = lobbyReference->searchForId(*itObjectID);
    if(object == nullptr) std::cout << "Lobby:moveMorph: encontre object " << morphId << std::endl;
    std::cout << "Lobby:moveMorph: encontre object" << object->getName() << std::endl;
    object->moveMorph(clientName, newX, newY);
}

void Lobby::interpretCodeGet(const std::string& code){
    std::vector<Object*> objectsCreated  = interpreter->interpretChar(code.c_str());
    for(auto itObject = objectsCreated.begin(); itObject != objectsCreated.end(); itObject++){
        auto itMorph = visibleObjects.find((*itObject)->getMorphId());
        if(itMorph == visibleObjects.end()) {
            visibleObjects.insert((*itObject)->getMorphId());
        }
        (*itObject)->notifyClients("crear");
    }
}

void Lobby::interpretCodeDo(const std::string& code){
    for(auto itVisibleObject = visibleObjects.begin(); itVisibleObject != visibleObjects.end(); itVisibleObject++){
        Object* visibleObject = lobbyReference->searchForId(*itVisibleObject);
        visibleObject->notifyClients("crear"); //TODO cambiar nombre de evento
    }
}


void Lobby::initializeMorphs() {
    std::cout << "Lobby::initializeMorphs: Empieza metodo" << std::endl;
    for (auto itObject = visibleObjects.begin(); itObject != visibleObjects.end(); itObject++) {
        std::cout << "Lobby::initializeMorphs Busco object" << *itObject << std::endl;
        std::cout << "Encuentro: " << lobbyReference->searchForId(*itObject)->getName() << std::endl;
        lobbyReference->searchForId(*itObject)->notifyClients("crear");
    }
}
