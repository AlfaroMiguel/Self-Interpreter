#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>
#include "morph.h"
#include "comunicador_server.h"
#include "cont_vistas.h"
#include "cont_eventos.h"
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
  ControladorVistas* cont_vistas;

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
  void set_control(ControladorEventos* cont_eventos);
  void iniciar();
  void editar();
  void mostrar_lobbies();
  void inicializar();
};
#endif
