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

	VentanaInicio* ventanaInicio = nullptr;
	builder->get_widget_derived("ventanaInicio", ventanaInicio);

	const std::string hostname(argv[1]);
	const std::string puerto(argv[2]);
	Modelo modelo(hostname, puerto);

	ventanaInicio->set_modelo(&modelo);
	std::cout << "2" << std::endl;
	app->run(*ventanaInicio);
	delete ventanaInicio;
	return 0;
}