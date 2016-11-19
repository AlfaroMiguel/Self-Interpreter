#ifndef LOBBY_DATA_HANDLER_H
#define LOBBY_DATA_HANDLER_H

#include "event_handler.h"
class LobbyDataHandler: public EventHandler{
 public:
  LobbyDataHandler(ControladorEventos* cont_eventos);
  ~LobbyDataHandler();
  void operator()();
 private:
  void handle(json j);
};
#endif