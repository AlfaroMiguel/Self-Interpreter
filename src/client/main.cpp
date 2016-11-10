#include <gtkmm.h>
#include <iostream>
#include "ventana_inicio.h"
#include "comunicador_server.h"
#include "modelo.h"

int main (int argc, char **argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ventana_vm.glade");

//	VentanaVM* ventanaVM = nullptr;
//	builder->get_widget_derived("ventanaPpal", ventanaVM);

	const std::string hostname(argv[1]);
	const std::string puerto(argv[2]);
	Modelo modelo(hostname, puerto);

	VentanaVM* ventana_vm = nullptr;
	builder->get_widget_derived("ventanaPpal", ventana_vm);

	ventana_vm->set_modelo(&modelo);

	app->run(*ventana_vm);
	delete ventana_vm;
	return 0;
}