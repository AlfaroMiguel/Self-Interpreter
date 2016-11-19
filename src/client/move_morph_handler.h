#ifndef MOVE_MORPH_HANDLER_H
#define MOVE_MORPH_HANDLER_H

#include "event_handler.h"
#include "client_handler.h"
class MoveMorphHandler: public EventHandler{
 public:
  MoveMorphHandler(ClientHandler* client_handler);
  ~MoveMorphHandler();
  void operator()();
 private:
  void handle(json j);
  bool on_handle(json j);
};
#endif