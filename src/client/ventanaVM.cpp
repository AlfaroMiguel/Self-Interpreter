#include "ventanaVM.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <vector>
#include <map>

#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"
#include "ventana_cliente.h"
#include "morph.h"

#define GLD_CAJA_EDITAR "cajaEditar"
#define GLD_CAJA_OBJETOS "cajaObjetos"

VentanaVM::VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
							Gtk::Window(cobject), builder(builder){
	maximize();
	builder->get_widget_derived(GLD_CAJA_EDITAR, ventana_edicion);
	builder->get_widget_derived(GLD_CAJA_OBJETOS, ventana_objetos);
	builder->get_widget_derived("dialogInicio", ventana_inicio);
	builder->get_widget_derived("dialogCliente", ventana_cliente);
	show_all_children();
	ventana_edicion->hide();
	ventana_objetos->hide();
	ventana_inicio->hide();
	ventana_cliente->present();
}

VentanaVM::~VentanaVM() {
	delete ventana_edicion;
	delete ventana_inicio;
	delete ventana_objetos;
	delete ventana_cliente;
	delete cont_vistas;
}

void VentanaVM::set_control(ClientHandler* client_handler){
	cont_vistas = new ControladorVistas(ventana_inicio, ventana_edicion, ventana_objetos, this, ventana_cliente);
	cont_vistas->set_control(client_handler);
}

bool VentanaVM::do_iniciar() {
	ventana_objetos->show();
	return false;
}

void VentanaVM::iniciar() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaVM::do_iniciar));
}

void VentanaVM::inicializar(){
	ventana_inicio->iniciar();
}

bool VentanaVM::do_editar(){
	ventana_edicion->show_all();
	return false;
}

void VentanaVM::editar(){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaVM::do_editar));
}