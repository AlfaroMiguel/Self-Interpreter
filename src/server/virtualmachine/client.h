#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Morph;

class Lobby;

class ProxyClient;

/*Clase que encapsula la informacion necesaria de un cliente, contiene su nombre,
 * una referencia a su proxy para comunicarse con el, y tambien una referencia al
 * lobby que se encuentra conectado acutalmente*/
class Client {
private:
    std::string clientName;
    ProxyClient *clientReference;
    Lobby *actualLobby;

public:
    /*Constructor recibe su nombre y una referencia a su proxy*/
    Client(std::string clientName, ProxyClient *clientReference);

    /*Destructor no libera ningun recurso ya que ninguno es adquirido en el constructor*/
    ~Client();

    /*Devuelve el nombre del cliente*/
    std::string getClientName() ;

    /*Recibe un puntero a un lobby y setea el lobby actual del cliente a ese lobby*/
    void setActualLobby(Lobby *newActualLobby);

    /*Devuelve el lobby actual del cliente*/
    Lobby *getActualLobby() ;

    /*Recibe el nombre del evento a notificar y una referencia a un morph y lo notifica*/
    void notify(std::string eventName, Morph &morph);
};

#endif
