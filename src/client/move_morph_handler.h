#ifndef MOVE_MORPH_HANDLER_H
#define MOVE_MORPH_HANDLER_H

#include "event_handler.h"
#include "cont_eventos.h"
class MoveMorphHandler: public EventHandler{
 public:
  MoveMorphHandler(ControladorEventos* cont_eventos);
  ~MoveMorphHandler();
  void operator()();
 private:
  void handle(json j);
  bool on_handle(json j);
};
#endif