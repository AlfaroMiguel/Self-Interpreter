#ifndef NEW_MORPH_HANDLER_H
#define NEW_MORPH_HANDLER_H

#include "event_handler.h"

/* Clase que maneja el evento "crear" */
class NewMorphHandler : public EventHandler {
 public:
  NewMorphHandler(ClientHandler *client_handler);
  ~NewMorphHandler();
 private:
  void handle(const json &j) const;
};
#endif
