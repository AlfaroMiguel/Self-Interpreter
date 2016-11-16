#include "virtualmachine.h"
#include "object.h"

VirtualMachine::VirtualMachine() {
    //Tengo que tener un lobby principal, por ahora lo hago compartido entre todos los clientes
    std::cout << "Creo maquina virtual" << std::endl;

    Object* lobbyObject = new Object();
    lobbyObject->setName("Lobby Principal");
    Lobby* lobby = new Lobby("Lobby Principal", true, lobbyObject);
    existingLobbies.insert(std::make_pair(lobby->getLobbyName(), lobby));

    std::cout << "Termino de crear maquina virtual" << std::endl;
}

VirtualMachine::~VirtualMachine() {
    //Aca tendria que entrar la serializacion de los lobbys, cuando se cierra la vm
}

Client* VirtualMachine::newClient(std::string clientName, ComunicadorCliente *clientReference) {
    Client* newClient =  new Client(clientName, clientReference);
    existingClients.insert(make_pair(clientName, newClient));
}

std::vector<std::string> VirtualMachine::getAvailablesLobbies(std::string client){
    std::vector<std::string> availablesLobbies;
    for(auto it = existingLobbies.begin(); it != existingLobbies.end(); it++){
        if(it->second->clientConnected(client) || it->second->isLobbyShared()){//Agrego si se conecto se cliente o el lobby es compartido
            availablesLobbies.push_back(it->second->getLobbyName());
        }
    }
    return availablesLobbies;
}

bool VirtualMachine::connectClient(std::string clientName, ComunicadorCliente* clientReference){
    auto itClient = existingClients.find(clientName);
    if(itClient != existingClients.end())
        return false;

    Client* client = newClient(clientName, clientReference);
    existingClients.insert(std::make_pair(clientName, client));
    return true;
}

void VirtualMachine::disconnectClient(std::string clientName){
    auto itClient = existingClients.find(clientName);
    if(itClient != existingClients.end())
        existingClients.erase(clientName);
    for(auto itLobbies = existingLobbies.begin(); itLobbies != existingLobbies.end(); itLobbies++){
        itLobbies->second->disconnectClient(itClient->second);
    }
}

bool VirtualMachine::connectClientToLobby(std::string clientName, std::string lobbyName, bool isShared) {
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

    lobby->connectClient(client);
    client->setActualLobby(lobby);
}