#ifndef VENTANA_OBJETOS_H
#define VENTANA_OBJETOS_H


#include "modelo.h"
#include <gtkmm.h>
#include <goocanvasmm.h>

class Morph;

class VentanaObjetos: public Gtk::Box{
 	public:
  		VentanaObjetos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  		~VentanaObjetos();

  		void dibujar_morph(Glib::RefPtr<Morph> morph);
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void set_control(ControladorEventos* cont_eventos);
  		void iniciar();
 	private:
  		ControladorEventos* cont_eventos;
  		Goocanvas::Canvas* canvas;
  		Glib::RefPtr<Goocanvas::Group> root;

  		bool on_button_press_event(GdkEventButton* event);
  		bool do_iniciar();
};
#endif