#include <gtkmm.h>
#include <iostream>
#include "main_view.h"
#include "server_proxy.h"
#include "modelo.h"
#include "ventana_edicion.h"
#include "ventana_inicio.h"
#include "ventana_objetos.h"
#include "client_handler.h"

int main (int argc, char **argv) {

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ventana_vm.glade");

	const std::string hostname(argv[1]);
	const std::string puerto(argv[2]);

	ServerProxy server_proxy(hostname, puerto);
	Modelo modelo;
	ClientHandler client_handler(&modelo, &server_proxy);

	server_proxy.set_control(&client_handler);
	modelo.set_control(&client_handler);

	MainView* main_view = nullptr;
	builder->get_widget_derived("ventanaPpal", main_view);

	main_view->set_control(&client_handler);

	app->run(*main_view);

	delete main_view;
	std::cout << "sale de la app" << std::endl;
	return 0;
}