#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include "morph.h"
#include "comunicador_server.h"

class VentanaVM: public Gtk::Window{
 private:
  Gtk::Box* caja_base;
  Gtk::Box* caja_editar;
  Gtk::Entry* entrada_nombre;
  Gtk::Entry* entrada_msj;
  int morphs_creados = 0;
  int morphs_activos = 1;
  Glib::RefPtr<Morph> morph_editando;
  ComunicadorServer com_server;
 public:
  VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~VentanaVM();
 protected:
  void click_objeto_nuevo();
  void crear_objeto();
  void on_eliminar_obj_event();
  void on_editar_nombre_event();
  void on_aceptar_nombre_event();
  void on_get_event();
  void on_do_event();
  void on_editar_obj_event();
  void on_finalizar_edicion_event();
  bool on_button_press_event(GdkEventButton* event);
  void agregar_slot(const Glib::ustring nombre_slot);
  void dibujar_morph(Glib::ustring nombre, double x, double y);
  void crear_menu_objetos();
  void ocultar_barra_edicion();
  double x, y;
  std::vector<Glib::RefPtr<Morph>> morphs;
  Goocanvas::Canvas* canvas;
  Glib::RefPtr<Goocanvas::GroupModel> root;
  Gtk::Menu menu_obj;
  Gtk::MenuItem objeto_nuevo;
  Gtk::MenuItem editar_objeto;
  Glib::RefPtr<Gtk::Builder> builder;
 public:
  void on_quit_click();
  void set_comunicador(ComunicadorServer& com_server);
};
#endif
