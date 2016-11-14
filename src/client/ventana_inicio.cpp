#include "ventana_inicio.h"

VentanaInicio::VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	builder->get_widget("opcLobbies", comboBox);
	builder->get_widget("btnConfirmar", boton_confirmar);
	boton_confirmar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_confirmar));
	builder->get_widget("entry1", entrada_nombre);
}

VentanaInicio::~VentanaInicio() {}

void VentanaInicio::set_lobby(const std::string& id){
	Glib::ustring lobby(id);
	lobbies.push_back(lobby);
}

void VentanaInicio::iniciar() {
	std::cout << lobbies.size() << std::endl;
	for(unsigned  int i = 0; i < lobbies.size(); i++) {
		std::cout << lobbies[i] << std::endl;
		comboBox->append(lobbies[i]);
	}
	if (lobbies.size() > 0)
		comboBox->set_active(0);
}

void VentanaInicio::set_control(ControladorEventos* cont_eventos) {
	this->cont_eventos = cont_eventos;
}

void VentanaInicio::on_confirmar(){
	const Glib::ustring lobby = comboBox->get_active_text();
	const Glib::ustring nombre = entrada_nombre->get_buffer()->get_text();
	hide();
	cont_eventos->abrir_vm(lobby.raw(), nombre.raw());
}



