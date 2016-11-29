#include "ventana_inicio.h"

#define GLD_LABEL_LOBBY "labelLobby"

VentanaInicio::VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	reseted = false;
	builder->get_widget("opcLobbies", comboBox);
	builder->get_widget("btnConfirmarLobby", boton_confirmar);
	builder->get_widget("btnSalirLobby", boton_salir);
	builder->get_widget("btnAgregarLobby", boton_agregar_lobby);
	builder->get_widget("btnSeleccionarLobby", boton_seleccionar_lobby);
	builder->get_widget("btnPrivado", boton_lobby_privado);
	builder->get_widget("btnCompartido", boton_lobby_compartido);
	builder->get_widget("entradaTexto", entrada_texto);
	builder->get_widget(GLD_LABEL_LOBBY, label_lobby);
	boton_agregar_lobby->join_group(*boton_seleccionar_lobby);
	boton_lobby_compartido->join_group(*boton_lobby_privado);
	boton_seleccionar_lobby->set_active();
	boton_lobby_privado->set_active();
	signal_confirm = boton_confirmar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_confirmar));
	boton_seleccionar_lobby->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_select_lobby));
	boton_agregar_lobby->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_add_lobby));
	boton_salir->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_quit));
}

VentanaInicio::~VentanaInicio() {}

void VentanaInicio::on_select_lobby(){
	comboBox->set_sensitive(true);
	entrada_texto->set_sensitive(false);
	boton_lobby_compartido->set_sensitive(false);
	boton_lobby_privado->set_sensitive(false);
}

void VentanaInicio::on_add_lobby(){
	entrada_texto->set_sensitive(true);
	boton_lobby_compartido->set_sensitive(true);
	boton_lobby_privado->set_sensitive(true);
	comboBox->set_sensitive(false);
}
void VentanaInicio::add_lobby(const std::string& lobby_id){
	Glib::ustring lobby(lobby_id);
	std::cout << "lobby recibido: " << lobby_id<< std::endl;
	std::cout << "size: " << lobbies.size()<< std::endl;
	bool is_existing_lobby = false;
	for(unsigned  int i = 0; i < lobbies.size(); i++) {
		if (lobbies[i] == lobby) {
			std::cout << "Lobbies: " << lobbies[i] << ", " << lobby.raw() << std::endl;
			is_existing_lobby = true;
		}
	}
	if (!is_existing_lobby) {
		std::cout << "Lobby agregado a lista: " << lobby_id << std::endl;
		lobbies.push_back(lobby);
	}
}

bool VentanaInicio::do_inicializar(){
	comboBox->remove_all();
	for(unsigned  int i = 0; i < lobbies.size(); i++) {
		std::cout << "Lobby agregado: " << lobbies[i] << std::endl;
		comboBox->append(lobbies[i]);
	}
	if (lobbies.size() > 0)
		comboBox->set_active(0);
	entrada_texto->set_sensitive(false);
	boton_lobby_compartido->set_sensitive(false);
	boton_lobby_privado->set_sensitive(false);
	return false;
}

void VentanaInicio::inicializar() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaInicio::do_inicializar));
}

void VentanaInicio::set_control(ClientHandler* client_handler) {
	this->client_handler = client_handler;
}

void VentanaInicio::on_confirmar(){
	std::cout << "entra a on_confirmar " << std::endl;
	Glib::ustring lobby;
	Glib::ustring estado("existente");
	if (boton_seleccionar_lobby->get_active())
		lobby = comboBox->get_active_text();
	else {
		lobby = entrada_texto->get_buffer()->get_text();
		if (boton_lobby_privado->get_active())
			estado = boton_lobby_privado->get_label();
		else
			estado = boton_lobby_compartido->get_label();
	}
	hide();
	reset();
	label_lobby->set_text(lobby);
	client_handler->select_lobby(lobby.raw(), estado.raw());
}

void VentanaInicio::on_change_lobby(){
	client_handler->reset_lobby();
	on_confirmar();
}

bool VentanaInicio::do_reset(){
	reseted = true;
	signal_confirm.disconnect();
	comboBox->set_active(0);
	comboBox->set_sensitive(true);
	entrada_texto->set_sensitive(false);
	boton_lobby_compartido->set_sensitive(false);
	boton_lobby_privado->set_sensitive(false);
	entrada_texto->get_buffer()->set_text("");
	boton_confirmar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_change_lobby));
	return false;
}
void VentanaInicio::reset(){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaInicio::do_reset));
}

void VentanaInicio::on_quit() {
	client_handler->quit();
}

bool VentanaInicio::on_key_release_event(GdkEventKey* eventKey){
	if (eventKey->keyval == GDK_KEY_Return){
		if (reseted)
			on_change_lobby();
		else
			on_confirmar();
	}
	return true;
}

