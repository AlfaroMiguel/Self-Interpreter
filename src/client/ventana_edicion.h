#ifndef VENTANA_EDICION_H
#define VENTANA_EDICION_H

#include "modelo.h"
#include "client_handler.h"
#include <gtkmm.h>

class VentanaEdicion: public Gtk::Box{
 	public:
  		VentanaEdicion(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  		~VentanaEdicion();

  		void set_control(ClientHandler* client_handler);
  		void start(const std::string& morph_name);
 	private:
  		Gtk::Entry* name_entry;
  		Gtk::TextView* code_entry;
  		Gtk::Button* boton_get;
  		Gtk::Button* boton_do;
  		Gtk::Button* boton_eliminar_obj;


  		double x_editando, y_editando;
  		ClientHandler* client_handler;

  		void on_eliminar_obj_event();
  		void on_editar_nombre_event();
  		void on_aceptar_nombre_event();
  		void on_get_event();
  		void on_do_event();
  		void on_finalizar_edicion_event();
  		void ocultar_barra_edicion();
  		bool do_start(const std::string& morph_name);
  		bool on_key_release_event(GdkEventKey* eventKey);

  		void send_code(const std::string& event);

  		VentanaEdicion(const VentanaEdicion& otra) = delete;
  		VentanaEdicion& operator=(const VentanaEdicion& otra) = delete;

};
#endif