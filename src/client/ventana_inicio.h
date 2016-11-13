#ifndef VENTANA_INICIO_H
#define VENTANA_INICIO_H

#include "modelo.h"
#include "cont_eventos.h"
#include <gtkmm.h>

class VentanaInicio: public Gtk::Dialog{
 public:
  	VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  	~VentanaInicio();

  	void set_lobby(const std::string& id);
  	void iniciar();
  	void set_control(ControladorEventos* cont_eventos);
  	void set_app(Glib::RefPtr<Gtk::Application> app);
 private:
  	std::vector<Glib::ustring> lobbies;
  	ControladorEventos* cont_eventos;

  	Glib::RefPtr<Gtk::Application> app;

  	Gtk::ComboBoxText* comboBox;
	Gtk::Button* boton_confirmar;
  	Gtk::Entry* entrada_nombre;

  	void on_confirmar();
	void on_quit_click();
};
#endif