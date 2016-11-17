#ifndef ADD_LOBBIES_HANDLER_H
#define ADD_LOBBIES_HANDLER_H

#include "event_handler.h"
#include "cont_eventos.h"

class AddLobbiesHandler: public EventHandler{
 public:
  AddLobbiesHandler(ControladorEventos* cont_eventos);
  ~AddLobbiesHandler();
  void operator()();
 private:
  void run(json j);
};
#endif