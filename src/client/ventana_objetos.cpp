#include "ventana_objetos.h"
#include <iostream>
#include "morph.h"
#include "drawing_area.h"

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


bool VentanaObjetos::do_draw_morph(Glib::RefPtr<Morph> morph) {
	root->add_child(morph);
	return false;
}

void VentanaObjetos::draw_morph(Glib::RefPtr <Morph> morph) {
	std::cout << "AGREGO MORPH: "<< morph->get_id() << std::endl;
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaObjetos::do_draw_morph), morph));
}

void VentanaObjetos::dismiss_morph(Glib::RefPtr<Morph> morph) {
	morph->dismiss();
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

bool VentanaObjetos::do_add_path(Glib::RefPtr <Goocanvas::Path> path) {
	root->add_child(path);
	return false;
}

void VentanaObjetos::add_path(Glib::RefPtr <Goocanvas::Path> path) {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaObjetos::do_add_path), path));
}

bool VentanaObjetos::do_delete_path(Glib::RefPtr <Goocanvas::Path> path){
	path->remove();
	return false;
}

void VentanaObjetos::delete_path(Glib::RefPtr <Goocanvas::Path> path) {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaObjetos::do_delete_path), path));
}