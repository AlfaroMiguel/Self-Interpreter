#include "ventanaVM.h"
#include "morph.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <vector>
#include <map>

#define GLD_CAJA_EDITAR "cajaEditar"
#define GLD_CAJA_OBJETOS "cajaObjetos"

VentanaVM::VentanaVM(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
							Gtk::Window(cobject), builder(builder){
	maximize();
	builder->get_widget_derived(GLD_CAJA_EDITAR, ventana_edicion);
	builder->get_widget_derived(GLD_CAJA_OBJETOS, ventana_objetos);
}

VentanaVM::~VentanaVM() {
	if (ventana_edicion) delete ventana_edicion;
	if (ventana_objetos) delete ventana_objetos;
}

void VentanaVM::set_modelo(Modelo* modelo){
	ventana_edicion->set_modelo(modelo);
	modelo->set_vista_objetos(ventana_objetos);
	ventana_objetos->set_modelo(modelo);
	modelo->set_vista_editar(ventana_edicion);
}

void VentanaVM::mostrar(){
	std::cout << "entro" << std::endl;
	show();
	show_all_children();
	ventana_edicion->hide();
}

void VentanaVM::on_quit_click() {
	hide();
}

