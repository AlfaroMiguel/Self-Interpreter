#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>
#include "../proxy_client.h"

/*Clase encargada en resolver todos los eventos posibles que surgan desde el cliente
 * Tiene los metodos encargados de cumplir las diferentes peticiones del mismo*/
class ServerHandler {
private:
    ProxyClient &client;
public:
    /*Recibe una referncia al cliente*/
    ServerHandler(ProxyClient &client);

    /*Destructor, no librea ningun recurso ya que ninguno es adquirido en el constructor*/
    ~ServerHandler();

    /*Recibe el nombre de un cliente y resuleve el evento de conectarlo con la maquina virtual*/
    void connect(const std::string &clientName);

    /*Inicializa todos los morphs de un cliente cuando este se conecta a un lobby y todavia
     * no tiene la informacion de los morphs que se encuentran en dicho lobby*/
    void initialize();

    /*Recibe el nombre de un lobby, y el estado del mismo, resuelve el evento que se produce cuando
     * un cliente elije un lobby al cual conectarse*/
    void chooseLobby(const std::string &lobbyName, const std::string &lobbyState);

    /*Recibe le id de un morph y los valores de su nueva posicion, se encarga de mover el morph
     * y notificar a los debidos clientes que acutalicen su posicion*/
    void moveMorph(int idMorph, double newX, double newY);

    /*Recibe el codigo self y resuelve el evento get*/
    void interpretSelfGet(const std::string &code, int morphID);

    /*Recibe el codigo self y resuelve el evento do*/
    void interpretSelfDo(const std::string &code, int morphID);

    /*Recibe el id del objeto y una referencia a una cadena indicando el nuevo nombre
     * cambia el nombre del objeto cambiando se representacion*/
    void changeObjectName(int objectID, const std::string &newName);

    /*Recibe el ID del morph y realiza un dismiss desapareciendo de la vista de todos los clientes
     * que se encuentre en ese lobby*/
    void dismissMorph(int moprhID);
};

#endif
