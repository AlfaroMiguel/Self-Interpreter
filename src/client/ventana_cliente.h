#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H
#include <gtkmm.h>
#include "cont_eventos.h"

class VentanaCliente: public Gtk::Dialog{
 public:
  VentanaCliente(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  ~VentanaCliente();

  void set_control(ControladorEventos* cont_eventos);
  void ocultar();

 private:
  ControladorEventos* cont_eventos;

  Gtk::Button* boton_ingresar;
  Gtk::Button* boton_salir;
  Gtk::Entry* entrada_texto;

  void on_ingresar();
  bool on_ocultar();
};
#endif