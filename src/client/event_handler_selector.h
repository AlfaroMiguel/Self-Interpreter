#ifndef EVENT_HANDLER_SELECTOR_H
#define EVENT_HANDLER_SELECTOR_H

#include "client_handler.h"
#include "event_handler.h"
#include <map>
#include <string>

/* Clase que se ocupa de seleccionar un manejador de eventos
 * segun el evento */
class EventHandlerSelector {
 public:
  EventHandlerSelector(ClientHandler *client_handler);
  ~EventHandlerSelector();

  /* Devuelve un manejador de eventos correspondiente al evento recibido */
  EventHandler *get_event_handler(const std::string &event);
 private:
  std::map<std::string, EventHandler *> event_handlers;
};
#endif
