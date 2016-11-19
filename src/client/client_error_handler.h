#ifndef CLIENT_ERROR_HANDLER_H
#define CLIENT_ERROR_HANDLER_H

#include "event_handler.h"

/* Clase functor que se ocupa de manejar el evento
 * de error en la conexion de un cliente */
class ClientErrorHandler : public EventHandler {
 private:
  void handle(json j);
 public:
  ClientErrorHandler(ClientHandler *client_handler);
  ~ClientErrorHandler();
};
#endif