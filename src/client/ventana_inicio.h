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
  	void mostrar_error();
 private:
  	std::vector<Glib::ustring> lobbies;
  	ControladorEventos* cont_eventos;


  	Gtk::ComboBoxText* comboBox;
	Gtk::Button* boton_confirmar;
  	Gtk::Button* boton_salir;
  	Gtk::RadioButton* boton_agregar_lobby;
  	Gtk::RadioButton* boton_seleccionar_lobby;
  	Gtk::RadioButton* boton_lobby_privado;
  	Gtk::RadioButton* boton_lobby_compartido;
  	Gtk::Entry* entrada_texto;
  	Gtk::Label* label_error;

  	void on_confirmar();
  	bool do_iniciar();
  	bool do_mostrar_error();
};
#endif