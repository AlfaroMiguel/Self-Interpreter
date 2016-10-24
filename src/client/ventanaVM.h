#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include "morph.h"

class VentanaVM: public Gtk::Window{
 private:
  Gtk::Box* caja_base;
  Gtk::Box* caja_editar;
  Gtk::Entry* entrada_nombre;
  Gtk::Entry* entrada_slot;
  int contador_morphs = 0;
 public:
  VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~VentanaVM();
 protected:
  void click_objeto_nuevo();
  void on_obj_nuevo_event();
  void on_eliminar_obj_event();
  void on_editar_nombre_event();
  void on_aceptar_nombre_event();
  void on_agregar_slot_event();
  void on_aceptar_slot_event();
  bool on_button_press_event(GdkEventButton* event);
  void dibujar_morph(double x, double y);
  void crear_menu_objetos();
  void ocultar_barra_edicion();
  double x, y;
  std::vector<Glib::RefPtr<Morph>> morphs;
  Goocanvas::Canvas* canvas;
  Glib::RefPtr<Goocanvas::GroupModel> root;
  Gtk::Menu menu_obj;
  Gtk::MenuItem objeto_nuevo;
  Gtk::MenuItem eliminar_objeto;
  Gtk::MenuItem editar_nombre;
  Gtk::MenuItem agregar_slot;
  Glib::RefPtr<Gtk::Builder> builder;
 public:
  void on_quit_click();
};
#endif
