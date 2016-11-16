#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "lobby.h"
#include <map>

class VirtualMachine{
private:
    //Tiene que tener un interpreter que dado un lobby y el codigo interprete el codigo
    std::map<std::string, Lobby*> existingLobbies;
    std::map<std::string, Client*> existingClients;

    Client* newClient(std::string clientName, ComunicadorCliente* clientReference);
public:
    VirtualMachine();
    ~VirtualMachine();

    std::vector<std::string> getAvailablesLobbies(std::string client);
    bool connectClient(std::string clientName, ComunicadorCliente* clientReference);
    bool connectClientToLobby(std::string clientName, std::string lobbyName, bool isShared);
    void disconnectClient(std::string clientName);
};

#endif