#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "server_handler.h"

class EventHandler{
 protected:
  EventHandler(const EventHandler& otra) = delete;
  EventHandler& operator=(const EventHandler& otra) = delete;

  ServerHandler* server_handler;
 public:
  EventHandler(ServerHandler* server_handler);
  virtual ~EventHandler();
  EventHandler(EventHandler&& otra);
  EventHandler& operator=(EventHandler&& otra);
  virtual void handle(json j) = 0;
};
#endif
