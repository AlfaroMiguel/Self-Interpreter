#include "ventana_objetos.h"
#include <iostream>
VentanaObjetos::VentanaObjetos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
								Gtk::Box(cobject){
	set_size_request(800, 800);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_hexpand(true);
	canvas->set_size_request(800,800);
	add(*canvas);
	root = Goocanvas::Group::create();
	canvas->set_root_item(root);
}

VentanaObjetos::~VentanaObjetos() {}


void VentanaObjetos::dibujar_morph(Glib::RefPtr<Morph> morph) {
	root->add_child(morph);
}

void VentanaObjetos::eliminar_morph(Glib::RefPtr<Morph> morph) {
	morph->eliminar();
}

void VentanaObjetos::set_modelo(Modelo* modelo) {
	this->modelo = modelo;
}

bool VentanaObjetos::on_button_press_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
		if (modelo->editar_morph(event->x, event->y)) {
			return true;
		}
	}
	if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		modelo->crear_morph_de_slot(event->x, event->y);
	}
	return false;
}

