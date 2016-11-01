#include "ventana_objetos.h"
#include <iostream>
VentanaObjetos::VentanaObjetos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
								Gtk::Box(cobject){
	std::cout << "CREANDO VENTANA OBJETOS" << std::endl;
	set_size_request(800, 800);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_hexpand(true);
	canvas->set_size_request(800,800);
	add(*canvas);
	root = Goocanvas::Group::create();
	canvas->set_root_item(root);
	std::cout << "VENTANA OBJETOS CREADA" << std::endl;
}

VentanaObjetos::~VentanaObjetos() {}


void VentanaObjetos::dibujar_morph(Glib::RefPtr<Morph> morph) {
	std::cout << "DIBUJANDO MORPH" << std::endl;
	//Glib::RefPtr<Goocanvas::Rect> rect = Goocanvas::Rect::create(10, 10, 10, 10);
	root->add_child(morph);
	std::cout << "MORPH DIBUJADO" << std::endl;
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
	return false;
}

