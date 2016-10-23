#ifndef MORPH_H
#define MORPH_H
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
class Morph: public Goocanvas::GroupModel {
 public:
  static Glib::RefPtr<Morph> create(double x, double y, double width, double height);
  Morph(double x, double y, double width, double height);
  ~Morph();
  void conectar_seniales(const Glib::RefPtr<Goocanvas::Item>& item);
  void eliminar();
  bool esta_en_posicion(double x, double y, Goocanvas::Canvas*);
 protected:
  Glib::RefPtr<Goocanvas::Item> dragging;
  int drag_x;
  int drag_y;
  std::vector<Glib::RefPtr<Goocanvas::Item>> items;
  Glib::RefPtr<Goocanvas::Rect> base;
  Glib::RefPtr<Goocanvas::Text> titulo;
  bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event);
};
#endif
