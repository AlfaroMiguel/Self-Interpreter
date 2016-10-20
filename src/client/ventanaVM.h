#ifndef VENTANAVM_H
#define VENTANAVM_H

#include <gtkmm.h>

class VentanaVM: public Gtk::Window{
 private:
  Gtk::Box* hbox;
 public:
  VentanaVM();
  virtual ~VentanaVM();
 protected:
  void click_objeto_nuevo();
 public:
  void on_quit_click();
};
#endif
