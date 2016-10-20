#include "ventanaVM.h"
#include "canvas_objetos.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

VentanaVM::VentanaVM() {
	set_default_size(600, 400);
	set_title("Self Virtual Machine");
	maximize();
	set_border_width(0);

	hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	add(*hbox);

	CanvasObj* canvas = Gtk::manage(new CanvasObj());
	hbox->set_homogeneous(false);
	hbox->set_center_widget(*canvas);

	show_all();
}

VentanaVM::~VentanaVM() {}

/*void VentanaVM::click_objeto_nuevo() {
	MyArea* area = Gtk::manage(new MyArea());
	hbox->add(*area);
	area->show();
	hbox->show();
}*/

void VentanaVM::on_quit_click() {
	hide();
}
