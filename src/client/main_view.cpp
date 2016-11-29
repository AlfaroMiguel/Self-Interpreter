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

#define GLD_EDIT_VIEW "cajaEditar"
#define GLD_OBJECT_VIEW "cajaObjetos"
#define GLD_LOBBY_WDW "dialogInicio"
#define GLD_CLIENT_WDW "dialogCliente"

MainView::MainView(BaseObjectType *cobject,
				   const Glib::RefPtr <Gtk::Builder> &builder) :
	Gtk::Window(cobject), builder(builder) {
	maximize();
	builder->get_widget_derived(GLD_EDIT_VIEW, editing_view);
	builder->get_widget_derived(GLD_OBJECT_VIEW, objects_view);
	builder->get_widget_derived(GLD_LOBBY_WDW, lobbies_view);
	builder->get_widget_derived(GLD_CLIENT_WDW, client_view);
	show_all_children();
	Gdk::RGBA rgba;
	rgba.set_rgba(0.8784, 0.8784, 0.8784);
	override_background_color(rgba);
	editing_view->hide();
	objects_view->hide();
	lobbies_view->hide();
	client_view->present();
}

MainView::~MainView() {
	delete editing_view;
	delete lobbies_view;
	delete objects_view;
	delete client_view;
	delete view_handler;
}

void MainView::set_handler(ClientHandler *client_handler) {
	view_handler = new ViewHandler(lobbies_view, editing_view,
								   objects_view, this, client_view);
	view_handler->set_control(client_handler);
}

bool MainView::do_quit() {
	hide();
	return false;
}

void MainView::quit() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &MainView::do_quit));
}