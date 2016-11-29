#include <gtkmm.h>
#include <iostream>
#include "main_view.h"
#include "server_proxy.h"
#include "model.h"
#include "ventana_edicion.h"
#include "ventana_inicio.h"
#include "ventana_objetos.h"
#include "client_handler.h"

#define GLD_MAIN_VIEW "ventanaPpal"
int main (int argc, char **argv) {

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ventana_vm.glade");

	const std::string hostname(argv[1]);
	const std::string puerto(argv[2]);

	ServerProxy server_proxy(hostname, puerto);
	Model model;
	ClientHandler client_handler(&model, &server_proxy);

	server_proxy.set_control(&client_handler);
	model.set_handler(&client_handler);

	MainView* main_view = nullptr;
	builder->get_widget_derived(GLD_MAIN_VIEW, main_view);

	main_view->set_handler(&client_handler);

	app->run(*main_view);

	delete main_view;

	return 0;
}