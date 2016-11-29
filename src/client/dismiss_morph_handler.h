#ifndef DISMISS_MORPH_HANDLER_H
#define DISMISS_MORPH_HANDLER_H

#include "event_handler.h"

/* Clase functor que se ocupa de manejar el evento "dismiss" */
class DismissMorphHandler : public EventHandler {
 public:
  DismissMorphHandler(ClientHandler *client_handler);
  ~DismissMorphHandler();
 private:
  void handle(const json &j) const;
};
#endif
