#include <gtkmm.h>
#include "ventanaVM.h"
#include "comunicador_server.h"

int main (int argc, char **argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("ventana_vm.glade");
	std::string hostname(argv[1]);
	std::string puerto(argv[2]);
	ComunicadorServer com_server(hostname, puerto);
	VentanaVM* ventanaVM = nullptr;
	builder->get_widget_derived("ventanaPpal", ventanaVM);
	ventanaVM->set_comunicador(com_server);
	app->run(*ventanaVM);
	delete ventanaVM;
	return 0;
}