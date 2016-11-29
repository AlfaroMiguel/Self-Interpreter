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
  	Gtk::Label* label_lobby;

  	bool reseted;

  	sigc::connection signal_confirm;

  	void on_confirmar();
  	bool do_inicializar();
  	void on_select_lobby();
  	void on_add_lobby();
  	void on_quit();
  	bool on_key_release_event(GdkEventKey* eventKey);
  	void reset();
  	void on_change_lobby();
  	bool do_reset();
};
#endif