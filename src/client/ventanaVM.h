#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include "morph.h"

class VentanaVM: public Gtk::Window{
 private:
  Gtk::Box* hbox;
 public:
  VentanaVM();
  virtual ~VentanaVM();
 protected:
  void click_objeto_nuevo();
  void on_obj_nuevo_event();
  void on_eliminar_obj_event();
  bool on_button_press_event(GdkEventButton* event);
  void dibujar_morph(double x, double y);
  void crear_menu_objetos();
  double x, y;
  std::vector<Glib::RefPtr<Morph>> morphs;
  Goocanvas::Canvas* canvas;
  Glib::RefPtr<Goocanvas::GroupModel> root;
  Gtk::Menu menu_obj;
  Gtk::MenuItem objeto_nuevo;
  Gtk::MenuItem eliminar_objeto;
 public:
  void on_quit_click();
};
#endif
