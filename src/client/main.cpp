#include <gtkmm.h>
#include <iostream>
#include "main_view.h"
#include "comunicador_server.h"
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

	ComunicadorServer com_server(hostname, puerto);
	Modelo modelo;
	ClientHandler client_handler(&modelo, &com_server);

	com_server.set_control(&client_handler);
	modelo.set_control(&client_handler);

	MainView* main_view = nullptr;
	builder->get_widget_derived("ventanaPpal", main_view);

	main_view->set_control(&client_handler);

	app->run(*main_view);

	delete main_view;

	return 0;
}