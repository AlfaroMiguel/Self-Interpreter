#include "ventana_inicio.h"

VentanaInicio::VentanaInicio(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	builder->get_widget("opcLobbies", comboBox);
	builder->get_widget("btnConfirmar", boton_confirmar);
	boton_confirmar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaInicio::on_confirmar));
	builder->get_widget("entry1", entrada_nombre);
}

VentanaInicio::~VentanaInicio() {}

void VentanaInicio::agregar_lobby(const std::string& id){
	Glib::ustring lobby(id);
	lobbies.push_back(lobby);
}

void VentanaInicio::iniciar() {
	for(unsigned  int i = 0; i < lobbies.size(); i++) {
		std::cout << lobbies[i] << std::endl;
		comboBox->append(lobbies[i]);
	}
	if (lobbies.size() > 0)
		comboBox->set_active(0);
}

void VentanaInicio::set_modelo(Modelo* modelo){
	this->modelo = modelo;
	modelo->inicializar();
}

void VentanaInicio::on_confirmar(){
	const Glib::ustring lobby = comboBox->get_active_text();
	const Glib::ustring nombre = entrada_nombre->get_buffer()->get_text();
	hide();
	ventana_vm->iniciar();
	//modelo->abrir_vm(ventana_vm, lobby.raw(), nombre.raw());
}

void VentanaInicio::set_vista_principal(VentanaVM* ventana_vm) {
	this->ventana_vm = ventana_vm;
}
