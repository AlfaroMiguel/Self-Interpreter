#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>
#include "morph.h"
#include "comunicador_server.h"
#include "view_handler.h"
#include "client_handler.h"
#include "ventana_cliente.h"

class VentanaEdicion;
class VentanaObjetos;
class VentanaInicio;

class VentanaVM: public Gtk::Window{
 private:
  VentanaEdicion* ventana_edicion;
  VentanaObjetos* ventana_objetos;
  VentanaInicio* ventana_inicio;
  VentanaCliente* ventana_cliente;
  ViewHandler* view_handler;

  Glib::RefPtr<Gtk::Builder> builder;

  bool do_iniciar();
  bool do_editar();
 public:
  VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~VentanaVM();

  VentanaVM(VentanaVM&& otra);
  VentanaVM& operator=(VentanaVM&& otra);

  //void actualizar_morph(std::string nombre, double x, double y, std::map<std::string, std::string> slots);
  void on_quit_click();
  void set_control(ClientHandler* client_handler);
  void iniciar();
  void editar();
  void mostrar_lobbies();
  void inicializar();
};
#endif
