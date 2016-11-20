#include "ventana_objetos.h"
#include <iostream>
#include "morph.h"

VentanaObjetos::VentanaObjetos(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
								Gtk::Box(cobject){
	set_size_request(800, 800);
	canvas = Gtk::manage(new Goocanvas::Canvas());
	canvas->set_hexpand(true);
	canvas->set_size_request(800,800);
	canvas->property_background_color_rgb() = 0xE0E0E0;
	add(*canvas);
	root = Goocanvas::Group::create();
	canvas->set_root_item(root);
}

VentanaObjetos::~VentanaObjetos() {}


bool VentanaObjetos::do_dibujar_morph(Glib::RefPtr<Morph> morph) {
	root->add_child(morph);
	return false;
}

void VentanaObjetos::dibujar_morph(Glib::RefPtr <Morph> morph) {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaObjetos::do_dibujar_morph), morph));
}

void VentanaObjetos::eliminar_morph(Glib::RefPtr<Morph> morph) {
	morph->eliminar();
}

void VentanaObjetos::set_control(ClientHandler* client_handler) {
	this->client_handler = client_handler;
}

bool VentanaObjetos::on_button_press_event(GdkEventButton *event) {
	return client_handler->button_event(event);
}

bool VentanaObjetos::do_start() {
	this->show();
	return false;
}

void VentanaObjetos::start() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &VentanaObjetos::do_start));
}

