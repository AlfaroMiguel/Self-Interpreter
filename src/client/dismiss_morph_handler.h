#ifndef DISMISS_MORPH_HANDLER_H
#define DISMISS_MORPH_HANDLER_H

#include "event_handler.h"
class DismissMorphHandler: public EventHandler{
 public:
  DismissMorphHandler(ClientHandler *client_handler);
  ~DismissMorphHandler();
 private:
  void handle(const json& j) const;
};
#endif