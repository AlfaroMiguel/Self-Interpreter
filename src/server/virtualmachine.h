#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "lobby.h"
#include <map>
/*Clase que representa la maquina virtual de Self, contiene toda la logica
 * e informacion acerca de los lobbies existentes y los clientes conectados*/
class VirtualMachine{
private:
    std::map<std::string, Lobby*> existingLobbies;
    std::map<std::string, Client*> existingClients;
    /*Recibe el nombre del cliente, una referencia a su proxy y crea un nuevo cliente
     * y guarda su informacion como cliente existente devuelve un puntero al cliente creado*/
    Client* newClient(const std::string& clientName, ProxyClient* clientReference);
    /*Recibe el nombre del cliente y devuelve un puntero al cliente existente en la maquina virtual*/
    Client* searchClient(const std::string& clientName);
public:
    /*Constructor de la maquina virtual, no recibe argumentos, crea un lobby
     * por defecto que es compartido llamado "Lobby principal"*/
    VirtualMachine();
    /*Destructor de la maquina virtual*/
    ~VirtualMachine();
    /*Recibe el nombre de un cliente y devuelve un vector con los nombres de los lobbies
     * disponibles que tiene para conectarse este cliente*/
    std::vector<std::string> getAvailablesLobbies(const std::string& client);
    /*Recibe el nombre de un cliente y una referencia al Proxy, si el cliente no existe lo crea
     * y lo agrega a los clientes existentes. Si el cliente ya existe actualiza la referencia del proxy
     * Devuelve si el cliente se pudo conectar o en cambio no porque el nombre ya existia*/
    bool connectClient(const std::string& clientName, ProxyClient* clientReference);
    /*Recibe el nombre de un cliente, el nombre de un lobby y si este es compartido o no,
     * setea este lobby al cliente como su lobby actual, en caso de no encontrarse el lobby lo crea.
        Devuelve si el cliente se pudo conectar al lobby */
    bool connectClientToLobby(const std::string& clientName, const std::string& lobbyName, bool isShared);
    /*Recibe el nombre de un cliente y lo desconecta, removiendolo de los clientes existentes y seteando
     * su referencia al proxy a null*/
    void disconnectClient(const std::string& clientName);
    /*Recibe una referencia al nombre del cliente, el id del Morph, la nueva posicion "x" y la nueva posicion "y" del morph
     * actualiza la posicion y notifica a los clientes conectados que se movio el morph*/
    void clientMovedMorph(const std::string& clientName, int morphId, double newX, double newY);
    /*Recibe una referencia al nombre del cliente, y una referencia al codigo self.
     * Interpreta el codigo self, y ademas notifica a los clientes de los cambios que fueron
     * producidos en los morphs*/
    void interpretCodeGet(const std::string& clientName, const std::string& code);
    /*Recibe una referencia al nombre del cliente, y una referencia al codigo self.
     * Interpreta el codigo self*/
    void interpretCodeDo(const std::string& clientName, const std::string& code);

};

#endif
