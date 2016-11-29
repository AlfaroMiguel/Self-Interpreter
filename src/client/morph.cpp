#include "morph.h"
#include "model.h"
#include "client_handler.h"
#include <vector>
#include <map>

#define ALTO 23
#define ANCHO 200

Morph::Morph(const Posicion &pos, const Glib::ustring &nombre, int id) :
	id(id) {
	object = MorphObject::create(pos, nombre, *this);
	Glib::signal_idle().connect
		(sigc::bind(sigc::mem_fun(*this, &Morph::do_create), object));
}

Morph::~Morph() {}

Morph::Morph(Morph &&otra) : dragging(otra.dragging), drag_x(otra.drag_x),
							 drag_y(otra.drag_y), object(otra.object),
							 id(otra.id) {}

Morph &Morph::operator=(Morph &&otra) {
	dragging = otra.dragging;
	drag_x = otra.drag_x;
	drag_y = otra.drag_y;
	object = otra.object;
	id = otra.id;
	return *this;
}

Glib::RefPtr <Morph> Morph::create(const Posicion &pos,
								   const Glib::ustring &nombre, int id) {
	return Glib::RefPtr<Morph>(new Morph(pos, nombre, id));
}

void Morph::set_handler(ClientHandler *client_handler) {
	this->client_handler = client_handler;
}

void Morph::connect_signals() {
	signal_button_press_event().connect
		(sigc::mem_fun(*this, &Morph::on_item_button_press_event));
	signal_button_release_event().connect
		(sigc::mem_fun(*this, &Morph::on_item_button_release_event));
	signal_motion_notify_event().connect
		(sigc::mem_fun(*this, &Morph::on_item_motion_notify_event));
}

void Morph::dismiss() {
	Glib::signal_idle().connect(sigc::mem_fun(*this, &Morph::do_dismiss));
}

bool Morph::is_in_position(const Posicion &pos) const {
	return object->is_in_position(pos);
}

void Morph::edit_name(const std::string &new_name) {
	Glib::ustring name(new_name);
	object->edit_name(name);
}

void Morph::add_slots(std::map<std::string, std::string> added_slots) {
	object->add_slots(added_slots);
}

double Morph::get_x() const {
	return object->get_x();
}

double Morph::get_y() const {
	return object->get_y();
}

int Morph::get_id() const {
	return id;
}

const std::string Morph::get_name() const {
	return object->get_name();
}

const std::string Morph::get_slot_value(const Posicion &slot_pos) const {
	return (object->get_slot_value(slot_pos)).raw();
}

const std::string Morph::get_slot_name(const Posicion &slot_pos) const {
	return (object->get_slot_name(slot_pos)).raw();
}

void Morph::move(const Posicion &new_pos) {
	object->move(new_pos);
	client_handler->update_morph_position(get_id(), get_position());
}

bool Morph::is_object(const Posicion &pos) const {
	return object->in_position(pos);
}

bool Morph::is_slot(const Posicion &pos) const {
	return object->slot_in_position(pos);
}

void Morph::change_position(const Posicion &new_pos) {
	object->change_position(new_pos);
}

const Posicion &Morph::get_position() const {
	return object->get_position();
}

bool Morph::has_id(int id) {
	return id == this->id;
}

void Morph::resize(double new_size) {
	object->resize_all(new_size);
}

void Morph::add_path_to_object(int id_padre, const std::string &slot_name) {
	object->add_path(id_padre, slot_name);
}

void Morph::add_path_to_slot(const std::string &slot_name, int id_padre) {
	object->add_path_to_slot(slot_name, id_padre);
}

const Posicion &Morph::get_slot_position(const std::string &slot_name) const {
	return object->get_slot_position(slot_name);
}

void Morph::add_union(int id, int id_padre, const std::string &slot_name) {
	client_handler->add_union(id, id_padre, slot_name);
}

bool Morph::shares_parent(int parent_id, const std::string &slot_name) {
	return object->shares_parent(parent_id, slot_name);
}

bool Morph::do_create(Glib::RefPtr <MorphObject> object) {
	add_child(object);
	return false;
}

bool Morph::do_dismiss() {
	object->remove();
	remove();
	return false;
}

bool Morph::on_item_button_press_event
	(const Glib::RefPtr <Goocanvas::Item> &item, GdkEventButton *event) {
	if (event->button == 1) {
		dragging = item;
		drag_x = (int) event->x;
		drag_y = (int) event->y;
	}
	return false;
}

bool Morph::on_item_button_release_event
	(const Glib::RefPtr <Goocanvas::Item> &item, GdkEventButton *event) {
	if (event->button == 1)
		dragging.reset();
	return false;
}

bool Morph::on_item_motion_notify_event
	(const Glib::RefPtr <Goocanvas::Item> &item, GdkEventMotion *event) {
	if (item && dragging && item == dragging) {
		Posicion new_pos(event->x - drag_x, event->y - drag_y);
		client_handler->move_morph(get_id(), new_pos);
	}
	return false;
}