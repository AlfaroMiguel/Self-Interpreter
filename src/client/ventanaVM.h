#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>
#include "morph.h"
#include "comunicador_server.h"
#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"

class VentanaVM: public Gtk::Window{
 private:
  VentanaEdicion* ventana_edicion;
  VentanaObjetos* ventana_objetos;
  VentanaInicio* ventana_inicio;
  Glib::RefPtr<Gtk::Builder> builder;
  Glib::RefPtr<Gtk::Application> app;

 public:
  VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~VentanaVM();

  VentanaVM(VentanaVM&& otra);
  VentanaVM& operator=(VentanaVM&& otra);

  //void actualizar_morph(std::string nombre, double x, double y, std::map<std::string, std::string> slots);
  void on_quit_click();
  void set_modelo(Modelo* modelo);
  void mostrar();
  void iniciar();
};
#endif
