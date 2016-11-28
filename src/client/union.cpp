#include "union.h"
#include "client_handler.h"
#include <iostream>
Union::Union(int id, int id_padre, const std::string& slot_name, ClientHandler* client_handler): id(id), id_padre(id_padre),
														  slot_name(slot_name), client_handler(client_handler){}
Union::~Union(){}

//static Glib::RefPtr<Union> Union::create(int id_padre, const std::string& slot_name){
//	return Glib::RefPtr<Union>(new Union(id_padre, slot_name));
//}

void Union::add_path(const Posicion& pos_begin, const Posicion& pos_end){
	std::string x_begin = std::to_string((int)pos_begin.get_x());
	std::string y_begin = std::to_string((int)pos_begin.get_y());
	std::string x_end = std::to_string((int)pos_end.get_x());
	std::string y_end = std::to_string((int)pos_end.get_y());
	std::string path_data("M "+x_begin+" "+y_begin+" L "+x_end+" "+y_end);
	std::cout << path_data << std::endl;
	path = Goocanvas::Path::create(path_data);
	client_handler->add_union(this);
}

void Union::update_path(const Posicion& pos_begin, const Posicion& pos_end){
	client_handler->delete_union(this);
	std::cout << "updates path" << std::endl;
	add_path(pos_begin, pos_end);
}

bool Union::operator==(const Union& other) const{
	return id_padre == other.id_padre && slot_name == other.slot_name && id == other.id;
}

bool Union::is_equal(const Union &other) {
	std::cout << "compara unions: " << std::endl;
	std::cout << "id_padre 1: " << id_padre << "id_padre 2: " << other.id_padre << std::endl;
	std::cout << "id 1: " << id << "id 2: " << other.id << std::endl;
	std::cout << "slot name 1: " << slot_name << "slot name 2: " << other.slot_name << std::endl;
	return id_padre == other.id_padre && slot_name == other.slot_name && id == other.id;
}

Glib::RefPtr<Goocanvas::Path> Union::get_path() const {
	return path;
}