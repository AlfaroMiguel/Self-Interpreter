#include "ventana_inicio.h"

VentanaInicio::VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	builder->get_widget("opcLobbies", comboBox);
	builder->get_widget("btnConfirmar", boton_confirmar);
	builder->get_widget("btnSalir", boton_salir);
	builder->get_widget("btnAgregarLobby", boton_agregar_lobby);
	builder->get_widget("btnSeleccionarLobby", boton_seleccionar_lobby);
	builder->get_widget("btnPrivado", boton_lobby_privado);
	builder->get_widget("btnCompartido", boton_lobby_compartido);
	builder->get_widget("entradaTexto", entrada_texto);
	builder->get_widget("lblError", label_error);
	boton_agregar_lobby->join_group(*boton_seleccionar_lobby);
	boton_lobby_compartido->join_group(*boton_lobby_privado);
	boton_seleccionar_lobby->set_active();
	boton_lobby_privado->set_active();
	boton_confirmar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_confirmar));
	label_error->hide();
}

VentanaInicio::~VentanaInicio() {}

void VentanaInicio::set_lobby(const std::string& id){
	Glib::ustring lobby(id);
	lobbies.push_back(lobby);
}

bool VentanaInicio::do_iniciar(){
	std::cout << lobbies.size() << std::endl;
	for(unsigned  int i = 0; i < lobbies.size(); i++) {
		std::cout << lobbies[i] << std::endl;
		comboBox->append(lobbies[i]);
	}
	if (lobbies.size() > 0)
		comboBox->set_active(0);
	show();
	return false;
}

void VentanaInicio::iniciar() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaInicio::do_iniciar));
}

void VentanaInicio::set_control(ControladorEventos* cont_eventos) {
	this->cont_eventos = cont_eventos;
}

void VentanaInicio::on_confirmar(){
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
	cont_eventos->abrir_vm(lobby.raw(), estado.raw());
}

bool VentanaInicio::do_mostrar_error(){
	label_error->show();
	entrada_texto->delete_text(0, entrada_texto->get_buffer()->get_text().size());
	return false;
}

void VentanaInicio::mostrar_error() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaInicio::do_mostrar_error));
}



