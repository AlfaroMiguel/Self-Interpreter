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

  		/* Dibuja el morph en la interfaz */
  		void draw_morph(Glib::RefPtr<Morph> morph);
  		/* Elimina el morph de la interfaz */
  		void dismiss_morph(Glib::RefPtr<Morph> morph);
  		void set_control(ClientHandler* client_handler);
  		void start();
  		void clear();
  		void join_morphs(const Posicion& pos_begin, const Posicion& pos_end);
  		void add_path(Glib::RefPtr<Goocanvas::Path> path);
  		void delete_path(Glib::RefPtr<Goocanvas::Path> path);

 private:
  		ClientHandler* client_handler;
  		Goocanvas::Canvas* canvas;
  		Glib::RefPtr<Goocanvas::Group> root;
  		Cairo::RefPtr <Cairo::Context> cr;

  		bool on_button_press_event(GdkEventButton* event);
  		/* Estos metodos permiten enviar las acciones de Gtk
  		 * al hilo principal */
  		bool do_start();
  		bool do_draw_morph(Glib::RefPtr<Morph> morph);
  		bool do_add_path(Glib::RefPtr<Goocanvas::Path> path);
  		bool do_delete_path(Glib::RefPtr <Goocanvas::Path> path);
};
#endif