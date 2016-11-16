#ifndef CLIENT_H
#define CLIENT_H


#include <string>
class Morph;
class Lobby;
class ComunicadorCliente;

class Client{
private:
    std::string clientName;
    ComunicadorCliente* clientReference;
    Lobby* actualLobby;

public:
    Client(std::string clientName, ComunicadorCliente* clientReference);
    ~Client();

    std::string getClientName();
    void setActualLobby(Lobby* newActualLobby);
    Lobby* getActualLobby();
    void notify(std::string eventName, Morph& morph);
};

#endif
