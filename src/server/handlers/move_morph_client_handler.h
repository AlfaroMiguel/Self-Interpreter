#ifndef MOVE_MORPH_CLIENT_HANDLER_H
#define MOVE_MORPH_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que el cliente movio un morph*/
class MoveMorphClientHandler : public EventHandler{
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);
public:
    /*Creador del handler recibe un puntero al Server Handler*/
    MoveMorphClientHandler(ServerHandler* server_handler);
    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~MoveMorphClientHandler();
};

#endif
