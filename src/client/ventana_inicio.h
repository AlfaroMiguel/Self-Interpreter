#ifndef VENTANA_INICIO_H
#define VENTANA_INICIO_H

#include "modelo.h"
#include "ventanaVM.h"
#include <gtkmm.h>

class VentanaInicio: public Gtk::Dialog{
 public:
  	VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  	~VentanaInicio();
  	void agregar_lobby(const std::string& id);
  	void iniciar();
  	void set_modelo(Modelo* modelo);
  	void set_vista_principal(VentanaVM* ventana_vm);
  	void set_app(Glib::RefPtr<Gtk::Application> app);
 private:
  	std::vector<Glib::ustring> lobbies;
  	Modelo* modelo;
  	VentanaVM* ventana_vm;

  	Glib::RefPtr<Gtk::Application> app;

  	Gtk::ComboBoxText* comboBox;
	Gtk::Button* boton_confirmar;
  	Gtk::Entry* entrada_nombre;

  	void on_confirmar();
	void on_quit_click();
};
#endif