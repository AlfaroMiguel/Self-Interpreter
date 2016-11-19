#ifndef NEW_MORPH_HANDLER_H
#define NEW_MORPH_HANDLER_H

#include "event_handler.h"
class NewMorphHandler: public EventHandler{
 public:
  NewMorphHandler(ClientHandler* client_handler);
  ~NewMorphHandler();
  void operator()();
 private:
  void handle(json j);
};
#endif