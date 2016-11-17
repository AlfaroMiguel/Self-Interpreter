#ifndef CONNECTED_CLIENT_HANDLER_H
#define CONNECTED_CLIENT_HANDLER_H

#include "event_handler.h"
#include "cont_eventos.h"
class ConnectedClientHandler: public EventHandler{
 public:
  ConnectedClientHandler(ControladorEventos* cont_eventos);
  ~ConnectedClientHandler();
  void operator()();
 private:
  void run(json j);
};
#endif