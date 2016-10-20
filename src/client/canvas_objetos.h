#ifndef CANVAS_OBJETOS_H
#define CANVAS_OBJETOS_H
#include <gtkmm.h>
#include <glibmm/main.h>
#include <goocanvasmm.h>

class CanvasObj: public Goocanvas::Canvas{
 public:
  CanvasObj();
  ~CanvasObj();
  void dibujar_morph();
 private:
  void on_obj_nuevo_event();
  bool on_button_press_event(GdkEventButton* event);
  double x, y;
  Glib::RefPtr<Goocanvas::Item> root;
  Gtk::Menu menu_der;
  Gtk::MenuItem objeto_nuevo;
};
#endif