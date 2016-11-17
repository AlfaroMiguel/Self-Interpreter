#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "lobby.h"
#include <map>

class VirtualMachine{
private:
    std::map<std::string, Lobby*> existingLobbies;
    std::map<std::string, Client*> existingClients;

    Client* newClient(std::string clientName, ComunicadorCliente* clientReference);
    Client* searchClient(std::string clientName);
public:
    VirtualMachine();
    ~VirtualMachine();

    std::vector<std::string> getAvailablesLobbies(std::string client);
    bool connectClient(std::string clientName, ComunicadorCliente* clientReference);
    bool connectClientToLobby(std::string clientName, std::string lobbyName, bool isShared);
    void disconnectClient(std::string clientName);
    void clientMovedMorph(std::string clientName, std::string morphName, double newX, double newY);
    void interpretCode(std::string clientName, std::string code);
};

#endif