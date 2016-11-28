#ifndef DISMISS_CLIENT_HANDLER_H
#define DISMISS_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que el cliente realizo un dismiss sobre
 * un Morph en la interfaz grafica*/
class DismissClientHandler : public EventHandler {
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);

public:
    /*Creador del handler recibe un puntero al Server Handler*/
    DismissClientHandler(ServerHandler *server_handler);

    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~DismissClientHandler();
};

#endif
