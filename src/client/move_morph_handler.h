#ifndef MOVE_MORPH_HANDLER_H
#define MOVE_MORPH_HANDLER_H

#include "event_handler.h"
#include "client_handler.h"

/* Clase que se encarga de manejar el evento "mover morph" */
class MoveMorphHandler: public EventHandler{
 public:
  MoveMorphHandler(ClientHandler* client_handler);
  ~MoveMorphHandler();
 private:
  void handle(const json& j) const;
  /* Realiza el metodo handle() en el hilo principal*/
  bool on_handle(const json& j) const;
};
#endif