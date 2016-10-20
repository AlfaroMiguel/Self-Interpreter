#include <gtkmm.h>
#include "ventanaVM.h"

int main (int argc, char **argv) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
	VentanaVM ventanaVM;
	return app->run(ventanaVM);
}