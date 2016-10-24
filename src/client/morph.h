#ifndef MORPH_H
#define MORPH_H
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
class Morph: public Goocanvas::GroupModel {
 public:
  static Glib::RefPtr<Morph> create(double x, double y, const Glib::ustring& nombre);
  Morph(double x, double y, const Glib::ustring& nombre);
  ~Morph();
  void conectar_seniales(Glib::RefPtr<Goocanvas::Item>& item);
  void eliminar();
  bool esta_en_posicion(double x, double y, Goocanvas::Canvas*);
  void editar_nombre(const Glib::ustring nombre_nuevo);
  void editando(bool valor);
  bool editando();
  void agregar_slot(const Glib::ustring nombre, Glib::RefPtr<Goocanvas::Item>& item);
 protected:
  Glib::RefPtr<Goocanvas::Item> dragging;
  int drag_x;
  int drag_y;
  bool siendo_editado;
  std::vector<Glib::RefPtr<Goocanvas::Item>> items;
  Glib::RefPtr<Goocanvas::Rect> base_titulo;
  Glib::RefPtr<Goocanvas::Text> titulo;
  std::vector<Glib::RefPtr<Morph>> slots;
  double pos_x, pos_y;
  bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event);
  void agregar_elementos(Glib::RefPtr<Goocanvas::Item>& item);
  void mover_elementos(double new_x, double new_y);
};
#endif
