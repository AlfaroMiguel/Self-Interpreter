#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "server_handler.h"

/*Clase padre representa a un EventHandler generico
 * Contiene una referencias al ServerHandler*/
class EventHandler {
protected:
    EventHandler(const EventHandler &otra) = delete;
    EventHandler &operator=(const EventHandler &otra) = delete;
    ServerHandler *server_handler;
public:
    /*Constructor, recibe un puntero al ServerHandler asociado*/
    EventHandler(ServerHandler *server_handler);

    /*Destructor virtual*/
    virtual ~EventHandler();

    /*Constructor por movimiento*/
    EventHandler(EventHandler &&otra);

    /*Operador asignacion por moviemiento*/
    EventHandler &operator=(EventHandler &&otra);

    /*Metodo abstracto puro*/
    virtual void handle(json j) = 0;
};

#endif
