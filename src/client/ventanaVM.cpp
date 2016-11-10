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
	builder->get_widget_derived("dialogInicio", ventana_inicio);
	show_all_children();
	ventana_inicio->set_vista_principal(this);
	ventana_edicion->hide();
	ventana_objetos->hide();
	ventana_inicio->present();
}

VentanaVM::~VentanaVM() {
	if (ventana_edicion) delete ventana_edicion;
	if (ventana_objetos) delete ventana_objetos;
	if (ventana_inicio) delete ventana_inicio;
}


void VentanaVM::set_modelo(Modelo* modelo){
	ventana_edicion->set_modelo(modelo);
	modelo->set_vista_objetos(ventana_objetos);
	ventana_objetos->set_modelo(modelo);
	modelo->set_vista_editar(ventana_edicion);
	std::cout << "ccaca" << std::endl;
	modelo->set_vista_inicio(ventana_inicio);
	ventana_inicio->set_modelo(modelo);
	std::cout << "ccaca1" << std::endl;
	std::cout << "ccaca2" << std::endl;
}

void VentanaVM::iniciar() {
	ventana_objetos->show();
}

