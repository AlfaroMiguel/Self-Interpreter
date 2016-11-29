#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "client_handler.h"

/* Clase functor que se ocupa de manejar eventos */
class EventHandler {
 protected:
  ClientHandler *client_handler;
 public:
  EventHandler(ClientHandler *client_handler);
  virtual ~EventHandler();
  /* Maneja un evento utilizando los datos del objeto json recibido */
  virtual void handle(const json &j) const = 0;
};
#endif
