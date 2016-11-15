#include "ventana_cliente.h"

VentanaCliente::VentanaCliente(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
	Gtk::Dialog(cobject){
	builder->get_widget("btnIngresar", boton_ingresar);
	builder->get_widget("btnSalir", boton_salir);
	builder->get_widget("entCliente", entrada_texto);
	boton_ingresar->signal_clicked().connect(sigc::mem_fun(*this, &VentanaCliente::on_ingresar));
}

VentanaCliente::~VentanaCliente() {}


void VentanaCliente::set_control(ControladorEventos* cont_eventos) {
	this->cont_eventos = cont_eventos;
}

void VentanaCliente::on_ingresar(){
	Glib::ustring nombre_cliente = entrada_texto->get_buffer()->get_text();
	std::cout << "Nombre cliente: " << nombre_cliente.raw() << std::endl;
	hide();
	cont_eventos->ingresar_cliente(nombre_cliente.raw());
}
