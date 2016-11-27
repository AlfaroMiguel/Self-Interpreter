#include "ventana_cliente.h"

VentanaCliente::VentanaCliente(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	builder->get_widget("btnIngresarCliente", boton_ingresar);
	builder->get_widget("btnSalirCliente", boton_salir);
	builder->get_widget("entCliente", entrada_texto);
	builder->get_widget("lblError", label_error);
	boton_ingresar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaCliente::on_ingresar));
	boton_salir->signal_clicked().connect(sigc::mem_fun(*this, &VentanaCliente::on_quit));
	label_error->hide();
}

VentanaCliente::~VentanaCliente() {}

void VentanaCliente::on_quit(){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaCliente::on_ocultar));
	client_handler->quit();
}

void VentanaCliente::set_control(ClientHandler* client_handler) {
	this->client_handler = client_handler;
}

void VentanaCliente::on_ingresar(){
	Glib::ustring client_name = entrada_texto->get_buffer()->get_text();
	std::cout << "Nombre cliente: " << client_name.raw() << std::endl;
	client_handler->connect_client(client_name.raw());
}

bool VentanaCliente::on_key_release_event(GdkEventKey* eventKey){
	if (eventKey->keyval == GDK_KEY_Return){
		on_ingresar();
	}
	return true;
}

bool VentanaCliente::on_ocultar() {
	hide();
	return false;
}

void VentanaCliente::ocultar(){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaCliente::on_ocultar));
}

bool VentanaCliente::do_mostrar_error(){
	label_error->show();
	entrada_texto->delete_text(0, entrada_texto->get_buffer()->get_text().size());
	return false;
}

void VentanaCliente::mostrar_error() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaCliente::do_mostrar_error));
}