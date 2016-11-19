#ifndef ADD_LOBBIES_HANDLER_H
#define ADD_LOBBIES_HANDLER_H

#include "event_handler.h"
class AddLobbiesHandler: public EventHandler{
 private:
  void handle(json j);
 public:
  AddLobbiesHandler(ClientHandler* client_handler);
  ~AddLobbiesHandler();
};
#endif