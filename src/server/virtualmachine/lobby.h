#ifndef JSON_LIB
#define JSON_LIB

#include "../../common/json.hpp"

using json = nlohmann::json;
#endif

#ifndef LOBBY_H
#define LOBBY_H

#include <string>
#include <vector>
#include <map>
#include <set>

#include "client.h"
#include "morph.h"
#include "../parser/interpreter.h"

/*Clase Lobby que contiene toda la informacion de un Lobby de Self
 * El nombre del lobby
 * Si es compartido o no
 * Una referencia al objeto lobby
 * Informacion sobre los clientes conectados este lobby
 * Una referencia al interpreter que interpretara el codigo self
 * Informacion sobre los objetos que son visibles en el lobby*/
class Lobby {
private:
    std::string lobbyName;
    bool isShared;
    Object *lobbyReference;
    std::map<std::string, Client *> clientsConnected;
    Interpreter *interpreter;
    std::set<int> visibleObjects;

public:
    /*Constructor vacio*/
    Lobby();

    /*Constructor: recibe el nombre del lobby, un valor booleano que indica si el lobby es compartiod, y
     * una referencia al objeto lobby*/
    Lobby(const std::string &lobbyName, bool isShared, Object *lobbyReference);

    /*Destructor del lobby*/
    ~Lobby();

    /*Devuelve el nombre del lobby*/
    std::string getLobbyName();

    /*Indica si un cliente esta conectado recibiendo el nombre del cliente*/
    bool clientConnected(const std::string &clientName);

    /*Indica si un cliente esta conectado al lobby recibiendo la referencia al clietne*/
    bool clientConnected(Client *client);

    /*Devuelve si el lobby es compartido*/
    bool isLobbyShared();

    /*Recibe una referencia a un cliente y lo conecta al lobby*/
    void connectClient(Client *client);

    /*Recibe una referencia a un cliente y lo desconecta del lobby*/
    void disconnectClient(Client *client);

    /*Recibe el nombre de evento a notificar, el nombre del cliente a notificar y una referncia al morph
     * notifica al cliente en cuestion con el nombre del evento y con el morph pasados por parametros*/
    void notifyClient(const std::string &eventName, const std::string &clientName, Morph &morph);

    /*Recibe un evento y un morph, opcionalmente puede recibir un nombre de un cliente
     * Notifica a todos los clientes con el nombre del evento excepto al cliente pasado por parametro*/
    void notifyClients(const std::string &eventName, Morph &morph, const std::string &clientNameUnnoified);

    /*Recibe el nombre de un cliente e inicializa a este cliente notificandole todos los morphs visibles*/
    void initializeClient(const std::string &clientName);

    /*Recibe el nombre del cliente que movio el morph, el id del morph, y su nueva posicion, actualica la posicion
     * de este morph y notifica a todos los clientes conectados al lobby excepto a si mismo del cambio*/
    void moveMorph(const std::string &clientName, int morphId, double newX, double newY);

    /*Recibe codigo self y lo interpreta ademas notifica a todos los clientes de los cambios producidos
     * y agrega a los objetos visibles los objetos creados o generados en la interpretacion del codigo*/
    void interpretCodeGet(const std::string &code, int objectContextID);

    /*Recibe codigo self y lo interpreta*/
    void interpretCodeDo(const std::string &code, int objectContextID);

    /*Inicializa todos los morphs visibles a los clientes conectados al lobby*/
    void initializeMorphs();

    /*Recibe el id del objeto y una cadena con el nuevo nombre
     * Cambia el nombre del objeto*/
    void changeObjectName(int objectID, const std::string &newName);

    /*Recibe el id de un Objeto, realiza un dismiss de ese objeto*/
    void dismissObject(int objectID);

    /*Serializacion*/
    /*Dado un json serializa el objeto lobby*/
    void serialize(json &jserialization);

    /*Dado un json deserializa el objeto lobby devolviendo un
     * puntero al objeto deserializado*/
    static Lobby *deserialize(json &jdeserialize);

};

#endif
