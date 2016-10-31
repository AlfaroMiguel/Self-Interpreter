#ifndef MORPH_H
#define MORPH_H
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>

#include "objeto.h"
#include "slot.h"

class Morph: public Goocanvas::Group {
 public:
  static Glib::RefPtr<Morph> create(double x, double y, Glib::ustring& nombre);
  Morph(double x, double y, Glib::ustring& nombre);
  ~Morph();
  void conectar_seniales();
  void eliminar();
  bool esta_en_posicion(double x, double y /* Goocanvas::Canvas* */);
  void editar_nombre(Glib::ustring nombre_nuevo);
  void editando(bool valor);
  bool editando();
  void agregar_slots(std::map<Glib::ustring, Glib::ustring> slots_a_agregar);
 protected:
  //const Glib::ustring& valor;
  Glib::RefPtr<Goocanvas::Item> dragging;
  int drag_x;
  int drag_y;
  bool siendo_editado = false;
  std::vector<Glib::RefPtr<Goocanvas::Item>> items;
 // void agregar_slot(const Glib::ustring& nombre, Glib::RefPtr<Goocanvas::Item>& item);
  //Glib::RefPtr<Goocanvas::Text> titulo;
  Glib::RefPtr<Objeto> objeto;
  std::vector<Glib::RefPtr<Slot>> slots;
  double pos_x, pos_y;
  bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event);
  void agregar_elementos();
  void mover_elementos(double new_x, double new_y);
};
#endif
