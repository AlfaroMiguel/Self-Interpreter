#include <gtkmm.h>
#include <iostream>
#include "ventanaVM.h"
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

	VentanaVM* ventana_vm = nullptr;
	builder->get_widget_derived("ventanaPpal", ventana_vm);

	ventana_vm->set_control(&client_handler);

	app->run(*ventana_vm);

	delete ventana_vm;

	return 0;
}