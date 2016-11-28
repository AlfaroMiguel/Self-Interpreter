#include "lobby.h"
#include "../parser/interpreter.h"
#include "iostream"

Lobby::Lobby(){}

Lobby::Lobby(const std::string& lobbyName, bool isShared, Object* lobbyReference) :
lobbyName(lobbyName), isShared(isShared), lobbyReference(lobbyReference){
    interpreter = new Interpreter(lobbyReference, this);
    std::string shellCode = "lobby _AddSlots: (| shell = (|  |).  |)."; //Ni bien se crea un interpreter le agrego la shell al lobby
    this->interpretCodeGet(shellCode, lobbyReference->getMorphId());
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
    std::cout << "Lobby::initializeClient start" << std::endl;
    auto itClient = clientsConnected.find(clientName);
    if(itClient != clientsConnected.end()) {
        if (itClient->second != nullptr) {
            this->initializeMorphs();
        }
    }
    std::cout << "Lobby::initializeClient end" << std::endl;
}

void Lobby::moveMorph(const std::string& clientName, int morphId, double newX, double newY){
    auto itObjectID = visibleObjects.find(morphId);
    if (itObjectID == visibleObjects.end())return;
    Object *object = lobbyReference->searchForId(*itObjectID);
    object->moveMorph(clientName, newX, newY);
}

void Lobby::interpretCodeGet(const std::string& code, int objectContextID){
    Object* objectContext = lobbyReference->searchForId(objectContextID);
    if(objectContext->getName() == "shell")objectContext = lobbyReference;
    std::cout << "Lobby::interpretCodeGet: interpreta: " << code << " y el Objecto contexto es " << objectContext->getName() << std::endl;
    interpreter->interpretChar(code.c_str(), objectContext);
    std::vector<Object*> objectsCreated  = interpreter->getCreatedObjets();
    for(auto itObject = objectsCreated.begin(); itObject != objectsCreated.end(); itObject++){
        auto itMorph = visibleObjects.find((*itObject)->getMorphId());
        if(itMorph == visibleObjects.end()) {
            visibleObjects.insert((*itObject)->getMorphId());
        }
        (*itObject)->notifyClients("crear");
    }
    interpreter->clearVectors();

    for(auto itVisibleObject = visibleObjects.begin(); itVisibleObject != visibleObjects.end(); itVisibleObject++){
        Object* visibleObject = lobbyReference->searchForId(*itVisibleObject);
        visibleObject->notifyClients("crear"); //TODO cambiar nombre de evento
    }
}

void Lobby::interpretCodeDo(const std::string& code, int objectContextID){
    Object* objectContext = lobbyReference->searchForId(objectContextID);
    if(objectContext->getName() == "shell")objectContext = lobbyReference;
    std::cout << "Lobby::interpretCodeDo: interpreta: " << code << " y el Objecto contexto es " << objectContext->getName() << std::endl;
    interpreter->interpretChar(code.c_str(), objectContext); //TODO notificar solo modificados
    for(auto itVisibleObject = visibleObjects.begin(); itVisibleObject != visibleObjects.end(); itVisibleObject++){
        Object* visibleObject = lobbyReference->searchForId(*itVisibleObject);
        visibleObject->notifyClients("crear"); //TODO cambiar nombre de evento
    }
}


void Lobby::initializeMorphs() {
    std::cout << "Lobby::initializeMorphs: start" << std::endl;
    for (auto itObject = visibleObjects.begin(); itObject != visibleObjects.end(); itObject++) {
        std::cout << "Lobby::initializeMorphs Busco object" << *itObject << std::endl;
        std::cout << "Encuentro: " << lobbyReference->searchForId(*itObject)->getName() << std::endl;
        lobbyReference->searchForId(*itObject)->notifyClients("crear"); //TODO cambiar nombre de evento
    }
    std::cout << "Lobby::initializeMorphs: end" << std::endl;
}

void Lobby::changeObjectName(int objectID, const std::string& newName){
    Object* object = lobbyReference->searchForId(objectID);
    if(object != nullptr){
        object->changeObjectName(newName);
        object->notifyClients("crear"); //TODO CAMBIAR NOMBRE DE EVENTO
    }
}

void Lobby::dismissObject(int objectID) {
    Object* object = lobbyReference->searchForId(objectID);
    auto itObjectID = visibleObjects.find(objectID);
    if(itObjectID != visibleObjects.end())visibleObjects.erase(itObjectID);
    if(object != nullptr){
        object->notifyClients("dismiss");
    }
}


/*Serializacion*/

void Lobby::serialize(json& jserialization){
    jserialization["lobbyName"] = lobbyName;
    jserialization["isShared"] = isShared;

    //Esta es la serializacion recursiva
    json jLobby;
    lobbyReference->serialize(jLobby);
    jserialization["lobbyReference"] = jLobby;

    json jClientsConnected;
    for(auto itClient = clientsConnected.begin(); itClient != clientsConnected.end(); itClient++){
        jClientsConnected.push_back(itClient->first);
    }
    jserialization["clientsConnected"] = jClientsConnected;

    json jVisibleObjects;
    for(auto itObject = visibleObjects.begin(); itObject != visibleObjects.end(); itObject++){
        jVisibleObjects.push_back(*itObject);
    }
    jserialization["visibleObjects"] = jVisibleObjects;
}

Lobby* Lobby::deserialize(json& jdeserialize){
    Lobby* lobby = new Lobby();

    lobby->lobbyName = jdeserialize["lobbyName"];
    lobby->isShared = jdeserialize["isShared"];

    json jLobby;
    jLobby = jdeserialize["lobbyReference"];

    lobby->lobbyReference = Object::deserialize(jLobby, lobby);

    json jClientsConnected = jdeserialize["clientsConnected"];
    for(auto it = jClientsConnected.begin(); it != jClientsConnected.end(); it++){
        std::string clientName = *it;
        Client* client = nullptr;
        lobby->clientsConnected.insert(std::make_pair(clientName, client));
    }

    lobby->interpreter = new Interpreter(lobby->lobbyReference, lobby);

    json jVisibleObjects = jdeserialize["visibleObjects"];
    for(auto it = jVisibleObjects.begin(); it != jVisibleObjects.end(); it++){
        int visibleObjectID = *it;
        lobby->visibleObjects.insert(visibleObjectID);
    }
    return lobby;
}
