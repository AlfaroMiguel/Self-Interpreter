#include "ventana_objetos.h"
#include <iostream>
#include "morph.h"
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

void VentanaObjetos::set_control(ControladorEventos* cont_eventos) {
	this->cont_eventos = cont_eventos;
}

bool VentanaObjetos::on_button_press_event(GdkEventButton *event) {
	return cont_eventos->button_event(event);
}

bool VentanaObjetos::do_iniciar() {
	this->show();
	return false;
}

void VentanaObjetos::iniciar() {
	sigc::connection conn = Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaObjetos::do_iniciar));
}

