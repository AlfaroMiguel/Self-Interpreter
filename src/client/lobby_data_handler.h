#ifndef LOBBY_DATA_HANDLER_H
#define LOBBY_DATA_HANDLER_H

#include "event_handler.h"
class LobbyDataHandler: public EventHandler{
 public:
  LobbyDataHandler(ClientHandler* client_handler);
  ~LobbyDataHandler();
  void operator()();
 private:
  void handle(json j);
};
#endif