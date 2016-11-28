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
	pack_start(*canvas);
	reorder_child(*canvas, 0);
	root = Goocanvas::Group::create();
	canvas->set_root_item(root);
//	LineDrawingArea myArea(canvas);
//	pack_start(myArea);
//	reorder_child(myArea, 0);
//	Glib::RefPtr<Goocanvas::Path> path = Goocanvas::Path::create("M 256.0 275.0 L 326.0 135.0");
//	root->add_child(path);
//	cr = canvas->create_cairo_context();
//	canvas->render(cr);
//	cr->set_source_rgb(0.8, 0.0, 0.0);
//	cr->move_to(0, 0);
//	cr->line_to(10, 10);
//	cr->stroke();
}

VentanaObjetos::~VentanaObjetos() {}


bool VentanaObjetos::do_draw_morph(Glib::RefPtr<Morph> morph) {
	root->add_child(morph);
	return false;
}

void VentanaObjetos::draw_morph(Glib::RefPtr <Morph> morph) {
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
	path->remove();
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &VentanaObjetos::do_delete_path), path));
}