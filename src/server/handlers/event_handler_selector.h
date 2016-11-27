#ifndef EVENT_HANDLER_SELECTOR_H
#define EVENT_HANDLER_SELECTOR_H

#include <map>
#include <string>

class ServerHandler;
class EventHandler;
class EventHandlerSelector{
 public:
  EventHandlerSelector(ServerHandler* client_handler);
  ~EventHandlerSelector();
  EventHandler* get_event_handler(const std::string& event);
 private:
  std::map<std::string, EventHandler*> event_handlers;
};
#endif