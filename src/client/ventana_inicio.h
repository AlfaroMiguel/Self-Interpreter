#ifndef VENTANA_INICIO_H
#define VENTANA_INICIO_H

#include "modelo.h"
#include "client_handler.h"
#include <gtkmm.h>

class VentanaInicio: public Gtk::Dialog{
 public:
  	VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  	~VentanaInicio();

  	/* Agrega un lobby a los lobbies en los que puede
	 * participar el cliente */
  	void add_lobby(const std::string& lobby_id);
  	void inicializar();
  	void set_control(ClientHandler* client_handler);
  	void mostrar_error();
 private:
  	std::vector<Glib::ustring> lobbies;
  	ClientHandler* client_handler;

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
  	bool do_inicializar();
  	bool do_mostrar_error();
  	void on_select_lobby();
  	void on_add_lobby();
  	void on_quit();
};
#endif