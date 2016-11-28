#ifndef ADD_LOBBIES_HANDLER_H
#define ADD_LOBBIES_HANDLER_H

#include "event_handler.h"

/* Clase functor que se encarga de manejar el evento
 * de agregar lobbies */
class AddLobbiesHandler : public EventHandler {
 public:
  AddLobbiesHandler(ClientHandler *client_handler);
  ~AddLobbiesHandler();
 private:
  void handle(const json &j) const;
};
#endif
