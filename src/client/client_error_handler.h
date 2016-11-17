#ifndef CLIENT_ERROR_HANDLER_H
#define CLIENT_ERROR_HANDLER_H

#include "event_handler.h"

class ClientErrorHandler: public EventHandler{
 public:
  ClientErrorHandler(ControladorEventos* cont_eventos);
  ~ClientErrorHandler();
  void operator()();
 private:
  void run(json j);
};
#endif