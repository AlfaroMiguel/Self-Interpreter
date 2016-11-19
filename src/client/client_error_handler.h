#ifndef CLIENT_ERROR_HANDLER_H
#define CLIENT_ERROR_HANDLER_H

#include "event_handler.h"

/*Clase functor que se ocupa de manejar el evento "error"*/
class ClientErrorHandler : public EventHandler {
 private:
  void handle(json j);
  void client_error(json j);
 public:
  ClientErrorHandler(ClientHandler *client_handler);
  ~ClientErrorHandler();
};
#endif