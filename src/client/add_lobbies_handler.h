#ifndef ADD_LOBBIES_HANDLER_H
#define ADD_LOBBIES_HANDLER_H

#include "event_handler.h"
class AddLobbiesHandler: public EventHandler{
 private:
  void handle(json j);
 public:
  AddLobbiesHandler(ControladorEventos* cont_eventos);
  ~AddLobbiesHandler();
};
#endif