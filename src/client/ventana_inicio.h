#ifndef VENTANA_INICIO_H
#define VENTANA_INICIO_H

#include "modelo.h"
#include "ventanaVM.h"
#include <gtkmm.h>

class VentanaInicio: public Gtk::Window{
 public:
  	VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  	~VentanaInicio();
  	void agregar_lobby(const std::string& id);
  	void iniciar();
  	void set_modelo(Modelo* modelo);
 private:
  	std::vector<Glib::ustring> lobbies;
  	Modelo* modelo;
  	VentanaVM* ventana_vm;

  	Gtk::ComboBoxText* comboBox;
	Gtk::Button* boton_confirmar;
  	Gtk::Entry* entrada_nombre;

  	void on_confirmar();

};
#endif