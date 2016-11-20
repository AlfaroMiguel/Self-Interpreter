#include "main_view.h"
#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gdkmm/rgba.h>
#include <vector>
#include <map>

#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"
#include "ventana_cliente.h"
#include "morph.h"

#define GLD_CAJA_EDITAR "cajaEditar"
#define GLD_CAJA_OBJETOS "cajaObjetos"

MainView::MainView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
							Gtk::Window(cobject), builder(builder){
	maximize();
	builder->get_widget_derived(GLD_CAJA_EDITAR, ventana_edicion);
	builder->get_widget_derived(GLD_CAJA_OBJETOS, ventana_objetos);
	builder->get_widget_derived("dialogInicio", ventana_inicio);
	builder->get_widget_derived("dialogCliente", ventana_cliente);
	show_all_children();
	Gdk::RGBA rgba;
	rgba.set_rgba(0.8784, 0.8784, 0.8784);
	override_background_color(rgba);
	ventana_edicion->hide();
	ventana_objetos->hide();
	ventana_inicio->hide();
	ventana_cliente->present();
}

MainView::~MainView() {
	delete ventana_edicion;
	delete ventana_inicio;
	delete ventana_objetos;
	delete ventana_cliente;
	delete view_handler;
}

void MainView::set_control(ClientHandler* client_handler){
	view_handler = new ViewHandler(ventana_inicio, ventana_edicion, ventana_objetos, this, ventana_cliente);
	view_handler->set_control(client_handler);
}