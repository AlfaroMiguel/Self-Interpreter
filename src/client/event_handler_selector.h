#ifndef EVENT_HANDLER_SELECTOR_H
#define EVENT_HANDLER_SELECTOR_H

#include "cont_eventos.h"
#include "event_handler.h"
#include <map>
#include <string>
class EventHandlerSelector{
 public:
  EventHandlerSelector(ControladorEventos* cont_eventos);
  ~EventHandlerSelector();
  EventHandler* get_event_handler(const std::string& event);
 private:
  std::map<std::string, EventHandler*> event_handlers;
};
#endif