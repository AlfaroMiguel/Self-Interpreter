#ifndef LOBBY_H
#define LOBBY_H

#include <string>
#include <vector>
#include <map>
#include "client.h"

class Object;

class Lobby{
private:
    std::string lobbyName;
    bool isShared;
    Object* lobbyReference;
    std::map<std::string, Client*> clientsConnected;
public:
    Lobby(std::string lobbyName, bool isShared, Object* lobbyReference);
    ~Lobby();

    std::string getLobbyName();

    bool clientConnected(std::string clientName);
    bool clientConnected(Client* client);

    bool isLobbyShared();

    void connectClient(Client* client);
    void disconnectClient(Client* client);
};

#endif