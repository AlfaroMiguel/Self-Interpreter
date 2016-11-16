#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "cont_eventos.h"

class EventHandler{
 protected:
  EventHandler(const EventHandler& otra) = delete;
  EventHandler& operator=(const EventHandler& otra) = delete;

  ControladorEventos* cont_eventos;
 public:
  EventHandler(ControladorEventos* cont_eventos);
  virtual ~EventHandler();
  EventHandler(EventHandler&& otra);
  EventHandler& operator=(EventHandler&& otra);
  virtual void run(json j) = 0;
};
#endif