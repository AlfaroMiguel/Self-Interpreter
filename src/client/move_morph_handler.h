#ifndef MOVE_MORPH_HANDLER_H
#define MOVE_MORPH_HANDLER_H

#include "event_handler.h"
#include "client_handler.h"
class MoveMorphHandler: public EventHandler{
 public:
  MoveMorphHandler(ClientHandler* client_handler);
  ~MoveMorphHandler();
 private:
  void handle(const json& j) const;
  bool on_handle(const json& j) const;
};
#endif