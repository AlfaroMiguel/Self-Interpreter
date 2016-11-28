#ifndef SELFTP_CHANGE_NAME_H
#define SELFTP_CHANGE_NAME_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que se recibe cuando un cliente
 * quiere cambiar de nombre a un Morph*/
class ChangeNameClientHandler : public EventHandler {
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);

public:
    /*Creador del handler recibe un puntero al Server Handler*/
    ChangeNameClientHandler(ServerHandler *server_handler);

    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~ChangeNameClientHandler();
};

#endif
