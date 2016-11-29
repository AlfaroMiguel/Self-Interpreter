#ifndef CONNECTED_CLIENT_HANDLER_H
#define CONNECTED_CLIENT_HANDLER_H

#include "event_handler.h"

/* Clase functor que se ocupa de manejar el evento "cliente conectado" */
class ConnectedClientHandler : public EventHandler {
 public:
  ConnectedClientHandler(ClientHandler *client_handler);
  ~ConnectedClientHandler();
 private:
  void handle(const json &j) const;
};
#endif
