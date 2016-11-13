#include "objeto.h"
#define ALTO 23
#define ANCHO 200

Objeto::Objeto(double pos_x, double pos_y, const Glib::ustring& nombre): Representacion(pos_x, pos_y, nombre){}

Glib::RefPtr<Objeto> Objeto::create(double pos_x, double pos_y, const Glib::ustring& nombre){
	return Glib::RefPtr<Objeto>(new Objeto(pos_x, pos_y, nombre));
}

Objeto::~Objeto(){}

Objeto::Objeto(Objeto&& otra): Representacion(otra.pos_x, otra.pos_y, otra.nombre), slots(otra.slots){}

Objeto& Objeto::operator=(Objeto&& otra){
	slots = otra.slots;
	return *this;
}

bool Objeto::esta_en_posicion(double x, double y){
	if (pos_x < x && pos_x + ANCHO > x  && pos_y < y && pos_y + ALTO> y) return true;
	for (unsigned int i = 0; i < slots.size(); i++)
		if (slots[i]->esta_en_posicion(x, y)) return true;
	return false;
}

void Objeto::agregar_slots(std::map<std::string, std::string> slots_a_agregar){
	std::map<std::string, std::string>::iterator it = slots_a_agregar.begin();
	while(it != slots_a_agregar.end()) {
		Glib::ustring nombre(it->first);
		Glib::ustring valor(it->second);
		int offset = ALTO*(slots.size()+1);
		Glib::RefPtr<Slot> slot_nuevo = Slot::create(pos_x, pos_y+offset, nombre, valor);
		slots.push_back(slot_nuevo);
		add_child(slot_nuevo);
		it++;
	}
}

void Objeto::mover(double new_x, double new_y){
	translate(new_x, new_y);
	actualizar_posicion(new_x, new_y);
	for (unsigned int i = 0; i < slots.size(); i++) {
		slots[i]->mover(new_x, new_y);
	}
}

void Objeto::editar_nombre(const Glib::ustring& nombre_nuevo){
	nombre = nombre_nuevo;
	texto->property_text() = nombre_nuevo;
}

Glib::ustring Objeto::obtener_nombre_slot(double x, double y){
	for (unsigned int i = 0; i < slots.size(); i++) {
		if (slots[i]->esta_en_posicion(x, y))
			return slots[i]->obtener_nombre();
	}
	Glib::ustring vacia;
	return vacia;
}

const std::string Objeto::get_nombre(){
	return nombre.raw();
}