#ifndef EVENT_HANDLER_SELECTOR_H
#define EVENT_HANDLER_SELECTOR_H

#include <map>
#include <string>

class ServerHandler;
class EventHandler;
/*Clase encargada de seleccionar los diferentes eventos y llamar a sus respectivos
 * handlers de cada EventHandler
 * Tiene una referecia al ServerHandler
 * Y un mapa con los diferentes nombres de los eventos posibles y como valor su EventHandler asociado*/
class EventHandlerSelector {

private:
    ServerHandler* server_handler;
    std::map<std::string, EventHandler *> event_handlers;

public:
    /*Recibe un puntero a un ServerHandler para tener referencia a este objeto
     * que se encarga de resolver los diferentes eventos*/
    EventHandlerSelector(ServerHandler *client_handler);

    /*Destructor, no libera ningun recurso ya que ninguno es adquirido en el cosntructor*/
    ~EventHandlerSelector();

    /*Recibe una referencia a una cadena con el nombre del evento y devuelve el EventHandler relacionado
     * que lo resuelve*/
    EventHandler* get_event_handler(const std::string &event);
};

#endif