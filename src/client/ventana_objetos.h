#ifndef VENTANA_OBJETOS_H
#define VENTANA_OBJETOS_H

#include "morph.h"
#include "modelo.h"
#include <gtkmm.h>
#include <goocanvasmm.h>

class VentanaObjetos: public Gtk::Box{
 	public:
  		VentanaObjetos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  		~VentanaObjetos();

  		void dibujar_morph(Glib::RefPtr<Morph> morph);
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void set_modelo(Modelo* modelo);
 	private:
  		Modelo* modelo;
  		Goocanvas::Canvas* canvas;
  		Glib::RefPtr<Goocanvas::Group> root;

  		bool on_button_press_event(GdkEventButton* event);
};
#endif