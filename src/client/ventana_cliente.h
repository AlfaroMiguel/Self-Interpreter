#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H
#include <gtkmm.h>
#include "client_handler.h"

class VentanaCliente: public Gtk::Dialog{
 public:
  VentanaCliente(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  ~VentanaCliente();

  void set_control(ClientHandler* client_handler);
  void ocultar();

 private:
  ClientHandler* client_handler;

  Gtk::Button* boton_ingresar;
  Gtk::Button* boton_salir;
  Gtk::Entry* entrada_texto;

  void on_ingresar();
  bool on_ocultar();
  bool on_key_release_event(GdkEventKey* eventKey);
  void on_quit();
};
#endif