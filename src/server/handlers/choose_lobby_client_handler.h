#ifndef CHOOSE_LOBBY_CLIENT_HANDLER_H/*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
#define CHOOSE_LOBBY_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que se recibe cuando un cliente
 * quiere cambiar de lobby*/
class ChooseLobbyClientHandler : public EventHandler {
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);

public:
    /*Creador del handler recibe un puntero al Server Handler*/
    ChooseLobbyClientHandler(ServerHandler *server_handler);

    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~ChooseLobbyClientHandler();
};

#endif