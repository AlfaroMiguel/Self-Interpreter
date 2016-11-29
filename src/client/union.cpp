#include "union.h"
#include "client_handler.h"
#include <iostream>
Union::Union(int id, int id_padre, const std::string& slot_name, ClientHandler* client_handler): id(id), id_padre(id_padre),
														  slot_name(slot_name), client_handler(client_handler){}
Union::~Union(){}

bool Union::on_add_path(const std::string& path_data){
	path = Goocanvas::Path::create(path_data);
	client_handler->add_union(this);
	return false;
}

void Union::add_path(const Posicion& pos_begin, const Posicion& pos_end){
	std::string x_begin = std::to_string((int)pos_begin.get_x());
	std::string y_begin = std::to_string((int)pos_begin.get_y());
	std::string x_end = std::to_string((int)pos_end.get_x());
	std::string y_end = std::to_string((int)pos_end.get_y());
	std::string path_data("M "+x_begin+" "+y_begin+" L "+x_end+" "+y_end);
	path = Goocanvas::Path::create(path_data);
	client_handler->add_union(this);
	//Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Union::on_add_path), path_data));
}

void Union::update_path(const Posicion& pos_begin, const Posicion& pos_end){
	client_handler->delete_union(this);
	add_path(pos_begin, pos_end);
}

bool Union::operator==(const Union& other) const{
	return id_padre == other.id_padre && slot_name == other.slot_name && id == other.id;
}

bool Union::is_equal(const Union &other) {
	return id_padre == other.id_padre && slot_name == other.slot_name && id == other.id;
}

Glib::RefPtr<Goocanvas::Path> Union::get_path() const {
	return path;
}