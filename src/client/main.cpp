#include <gtkmm.h>
#include <iostream>
#include "ventanaVM.h"
#include "comunicador_server.h"
#include "modelo.h"
#include "ventana_edicion.h"
#include "ventana_inicio.h"
#include "ventana_objetos.h"
#include "cont_vistas.h"
#include "cont_eventos.h"

int main (int argc, char **argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ventana_vm.glade");

	const std::string hostname(argv[1]);
	const std::string puerto(argv[2]);

	ComunicadorServer com_server(hostname, puerto);
	Modelo modelo;
	ControladorEventos cont_eventos(&modelo, &com_server);

	com_server.set_control(&cont_eventos);
	modelo.set_control(&cont_eventos);

	VentanaVM* ventana_vm = nullptr;
	builder->get_widget_derived("ventanaPpal", ventana_vm);

	ventana_vm->set_control(&cont_eventos);

	com_server.inicializar();

	app->run(*ventana_vm);

	delete ventana_vm;

	return 0;
}