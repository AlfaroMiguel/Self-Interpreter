#ifndef LOBBY_H
#define LOBBY_H

#include <string>
#include <vector>
#include <map>
#include "client.h"
#include "morph.h"

class Interpreter;
class Object;

class Lobby{
private:
    std::string lobbyName;
    bool isShared;
    Object* lobbyReference;
    std::map<std::string, Client*> clientsConnected;
    Interpreter* interpreter;

public:
    Lobby(std::string lobbyName, bool isShared, Object* lobbyReference);
    ~Lobby();

    std::string getLobbyName();

    bool clientConnected(std::string clientName);
    bool clientConnected(Client* client);

    bool isLobbyShared();

    void connectClient(Client* client);
    void disconnectClient(Client* client);

    void notifyClient(std::string eventName, std::string clientName, Morph& morph);
    void notifyClients(std::string eventName, Morph& morph);
    void initializeClient(std::string clientName);

    void moveMorph(std::string morphName, double newX, double newY);

    void interpretCode(std::string code);
};

#endif