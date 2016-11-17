#include "objeto.h"
#define ALTO 23
#define ANCHO 200

Objeto::Objeto(const Posicion& pos, const Glib::ustring& nombre): Representacion(pos, nombre){}

Glib::RefPtr<Objeto> Objeto::create(const Posicion& pos, const Glib::ustring& nombre){
	return Glib::RefPtr<Objeto>(new Objeto(pos, nombre));
}

Objeto::~Objeto(){}

Objeto::Objeto(Objeto&& otra): Representacion(otra.posicion, otra.nombre), slots(otra.slots){}

Objeto& Objeto::operator=(Objeto&& otra){
	slots = otra.slots;
	return *this;
}

bool Objeto::esta_en_posicion(const Posicion& pos_comparar) const{
	if (objeto_en_posicion(pos_comparar)) return true;
	if (slot_en_posicion(pos_comparar)) return true;
	return false;
}

void Objeto::agregar_slots(std::map<std::string, std::string> slots_a_agregar){
	std::map<std::string, std::string>::iterator it = slots_a_agregar.begin();
	while(it != slots_a_agregar.end()) {
		Glib::ustring nombre(it->first);
		Glib::ustring valor(it->second);
		int offset = ALTO*(slots.size()+1);
		Posicion pos_slot(posicion.get_x(), posicion.get_y()+offset);
		Glib::RefPtr<Slot> slot_nuevo = Slot::create(pos_slot, nombre, valor);
		slots.push_back(slot_nuevo);
		add_child(slot_nuevo);
		it++;
	}
}

bool Objeto::on_cambiar_posicion(Posicion* pos){
	double x = pos->get_x();
	double y = pos->get_y();
	double offset_x = x - posicion.get_x();
	double offset_y = y - posicion.get_y();
	posicion.set_x(x);
	posicion.set_y(y);
	translate(offset_x, offset_y);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(offset_x, offset_y);
	return false;
}

void Objeto::cambiar_posicion(Posicion* pos){
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Objeto::on_cambiar_posicion), pos));
}

void Objeto::mover(double new_x, double new_y){
	translate(new_x, new_y);
	actualizar_posicion(new_x, new_y);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(new_x, new_y);
	std::cout << "La posicion del objeto es: " << posicion.get_x() << ", " << posicion.get_y() << std::endl;
}

void Objeto::editar_nombre(const Glib::ustring& nombre_nuevo){
	std::cout << "Nombre anterior: " << nombre.raw() << std::endl;
	nombre = nombre_nuevo;
	std::cout << "Nombre nuevo: " << nombre.raw() << std::endl;
	texto->property_text() = nombre_nuevo;
}

Glib::ustring Objeto::obtener_valor_slot(const Posicion& pos) const{
	for (unsigned int i = 0; i < slots.size(); i++) {
		if (slots[i]->esta_en_posicion(pos))
			return slots[i]->obtener_valor();
	}
	Glib::ustring vacia;
	return vacia;
}

Glib::ustring Objeto::obtener_nombre_slot(const Posicion& pos) const{
	for (unsigned int i = 0; i < slots.size(); i++) {
		if (slots[i]->esta_en_posicion(pos)) {
			return slots[i]->obtener_nombre();
		}
	}
	Glib::ustring vacia;
	return vacia;
}

const std::string Objeto::get_nombre() {
	return nombre.raw();
}

bool Objeto::objeto_en_posicion(const Posicion& pos_comparar) const {
	Posicion pos_max(posicion.get_x()+ANCHO, posicion.get_y()+ALTO);
	return posicion < pos_comparar && pos_max > pos_comparar;
}

bool Objeto::slot_en_posicion(const Posicion& pos_comparar) const{
	for (unsigned int i = 0; i < slots.size(); i++)
		if (slots[i]->esta_en_posicion(pos_comparar)) return true;
	return false;
}