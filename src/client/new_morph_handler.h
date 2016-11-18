#ifndef NEW_MORPH_HANDLER_H
#define NEW_MORPH_HANDLER_H

#include "cont_eventos.h"
#include "event_handler.h"
class NewMorphHandler: public EventHandler{
 public:
  NewMorphHandler(ControladorEventos* cont_eventos);
  ~NewMorphHandler();
  void operator()();
 private:
  void handle(json j);
};
#endif