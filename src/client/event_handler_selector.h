#ifndef EVENT_HANDLER_SELECTOR_H
#define EVENT_HANDLER_SELECTOR_H

#include "client_handler.h"
#include "event_handler.h"
#include <map>
#include <string>

class EventHandlerSelector{
 public:
  EventHandlerSelector(ClientHandler* client_handler);
  ~EventHandlerSelector();
  EventHandler* get_event_handler(const std::string& event);
 private:
  std::map<std::string, EventHandler*> event_handlers;
};
#endif