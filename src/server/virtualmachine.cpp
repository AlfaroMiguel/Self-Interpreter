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

void VirtualMachine::newClient(std::string clientName, ComunicadorCliente *clientReference) {
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


