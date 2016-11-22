#include "virtualmachine.h"
#include "object.h"

Client* VirtualMachine::newClient(const std::string& clientName, ProxyClient *clientReference) {
    Client* newClient =  new Client(clientName, clientReference);
    existingClients.insert(make_pair(clientName, newClient));
    return newClient;
}

Client* VirtualMachine::searchClient(const std::string& clientName){
    auto itClient = existingClients.find(clientName);
    if(itClient == existingClients.end())
        return nullptr;

    return itClient->second;
}

VirtualMachine::VirtualMachine() {
    //Tengo que tener un lobby principal, por ahora lo hago compartido entre todos los clientes
    std::cout << "Iniciando maquina virtual" << std::endl;
    Object* lobbyObject = new Object();
    lobbyObject->setName("Lobby Principal");
    Lobby* lobby = new Lobby("Lobby Principal", true, lobbyObject);
    existingLobbies.insert(std::make_pair(lobby->getLobbyName(), lobby));
    std::cout << "Maquina virtual de Self corriendo" << std::endl;
}

VirtualMachine::~VirtualMachine() {}

std::vector<std::string> VirtualMachine::getAvailablesLobbies(const std::string& client){
    std::vector<std::string> availablesLobbies;
    for(auto it = existingLobbies.begin(); it != existingLobbies.end(); it++){
        if(it->second->clientConnected(client) || it->second->isLobbyShared()){//Agrego si se conecto se client o el lobby es compartido
            availablesLobbies.push_back(it->second->getLobbyName());
        }
    }
    return availablesLobbies;
}

bool VirtualMachine::connectClient(const std::string& clientName, ProxyClient* clientReference){
    auto itClient = existingClients.find(clientName);
    if(itClient != existingClients.end())
        return false;

    Client* client = newClient(clientName, clientReference);
    existingClients.insert(std::make_pair(clientName, client));
    return true;
}

void VirtualMachine::disconnectClient(const std::string& clientName){
    auto itClient = existingClients.find(clientName);
    if(itClient != existingClients.end())
        existingClients.erase(clientName);
    for(auto itLobbies = existingLobbies.begin(); itLobbies != existingLobbies.end(); itLobbies++){
        itLobbies->second->disconnectClient(itClient->second);
    }
}

bool VirtualMachine::connectClientToLobby(const std::string& clientName,const std::string& lobbyName, bool isShared) {
    auto itClient = existingClients.find(clientName);
    if(itClient == existingClients.end())
        return false;

    Client* client = itClient->second;

    auto itLobby = existingLobbies.find(lobbyName);
    Lobby* lobby;
    if(itLobby == existingLobbies.end()){
        Object* lobbyObject = new Object();
        lobbyObject->setName(lobbyName);
        lobby = new Lobby(lobbyName, isShared, lobbyObject);
        existingLobbies.insert(std::make_pair(lobby->getLobbyName(), lobby));
    }
    else
        lobby = itLobby->second;

    std::cout << "Connect Client: "<< clientName << "to lobby: "<< lobbyName << std::endl;
    lobby->connectClient(client);
    client->setActualLobby(lobby);
}

void VirtualMachine::clientMovedMorph(const std::string& clientName, int morphId, double newX, double newY){
    auto itClient = existingClients.find(clientName);
    if(itClient == existingClients.end())
        return;

    Client* client = itClient->second;
    Lobby* lobby = client->getActualLobby();
    lobby->moveMorph(clientName, morphId, newX, newY);
}

void VirtualMachine::interpretCodeGet(const std::string& clientName, const std::string& code){
    Client* client = searchClient(clientName);
    if(client != nullptr){
        Lobby* lobby = client->getActualLobby();
        std::cout << "El lobby actual de: " << clientName << " es " << lobby->getLobbyName() << std::endl;
        lobby->interpretCodeGet(code);
    }
}

void VirtualMachine::interpretCodeDo(const std::string& clientName, const std::string& code){
    Client* client = searchClient(clientName);
    if(client != nullptr){
        Lobby* lobby = client->getActualLobby();
        std::cout << "El lobby actual de: " << clientName << " es " << lobby->getLobbyName() << std::endl;
        lobby->interpretCodeDo(code);
    }
}
