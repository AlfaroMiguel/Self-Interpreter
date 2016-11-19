#ifndef CONTROLADOR_EVENTOS_H
#define CONTROLADOR_EVENTOS_H

#include <string>
class ProxyClient;

class EventHandler {
private:
    ProxyClient& client;

    void connect(std::string clientName);
    void initialize();
    void chooseLobby(std::string lobbyName, std::string lobbyState);
    void moveMorph(int idMorph, double newX, double newY);
    void interpretSelfGet(std::string code);
    void interpretSelfDo(std::string code);

public:
    EventHandler(ProxyClient& client);
    ~EventHandler();
    void handleEvent(std::string event);
};


#endif
