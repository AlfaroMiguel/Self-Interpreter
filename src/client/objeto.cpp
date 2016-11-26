#include "objeto.h"
#include "morph.h"
#define ALTO 23
#define ANCHO 200
#define WIDTH_PER_CHARACTER 10

#include "../common/lock.h"
Objeto::Objeto(const Posicion& pos, const Glib::ustring& nombre,
			   Morph& parent_morph):
	Representacion(pos, nombre, parent_morph){}

Glib::RefPtr<Objeto> Objeto::create(const Posicion& pos,
									const Glib::ustring& nombre,
									Morph& parent_morph){
	return Glib::RefPtr<Objeto>(new Objeto(pos, nombre, parent_morph));
}

Objeto::~Objeto(){}

Objeto::Objeto(Objeto&& otra): Representacion(otra.posicion, otra.nombre, otra.parent_morph),
							   slots(otra.slots){}

Objeto& Objeto::operator=(Objeto&& otra){
	slots = otra.slots;
	return *this;
}

bool Objeto::esta_en_posicion(const Posicion& pos_comparar) const{
	if (objeto_en_posicion(pos_comparar)) return true;
	if (slot_en_posicion(pos_comparar)) return true;
	return false;
}

bool Objeto::on_agregar_slot(Glib::RefPtr<Slot> slot){
	add_child(slot);
	return false;
}


void Objeto::agregar_slots(std::map<std::string, std::string> slots_a_agregar){
	int slots_agregados = 0;
	int offset;
	std::map<std::string, std::string>::iterator it = slots_a_agregar.begin();
	while(it != slots_a_agregar.end()) {
		Glib::ustring nombre(it->first);
		Glib::ustring valor(it->second);
		if (slots_agregados == 0)
			offset = (ALTO*(slots.size()+1)) + 2.5;
		else
			offset =(ALTO*(slots.size()+1));
		Posicion pos_slot(posicion.get_x(), posicion.get_y()+offset);
		Glib::RefPtr<Slot> slot_nuevo = Slot::create(pos_slot, nombre, valor, parent_morph);
		slots.push_back(slot_nuevo);
		Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Objeto::on_agregar_slot), slot_nuevo));
		it++;
		slots_agregados++;
	}
}

bool Objeto::on_cambiar_posicion(const Posicion* pos){
	double x = pos->get_x();
	double y = pos->get_y();
	posicion.set_x(x);
	posicion.set_y(y);
	double offset_x = x - posicion.get_x();
	double offset_y = y - posicion.get_y();
	translate(offset_x, offset_y);
	Posicion pos_slot(offset_x, offset_y);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(pos_slot);
	return false;
}

void Objeto::cambiar_posicion(const Posicion& pos){
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Objeto::on_cambiar_posicion), &pos));
}

bool Objeto::on_mover(const Posicion* new_pos){
	double new_x = new_pos->get_x();
	double new_y = new_pos->get_y();
	translate(new_x, new_y);
	actualizar_posicion(*new_pos);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(*new_pos);
	return false;
}
void Objeto::mover(const Posicion& new_pos){
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Objeto::on_mover), &new_pos));
}

void Objeto::editar_nombre(const Glib::ustring& nombre_nuevo){
	nombre = nombre_nuevo;
	if (needs_resize(nombre.raw().size()*WIDTH_PER_CHARACTER))
		resize_all((nombre.raw().size())*WIDTH_PER_CHARACTER);
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

const Posicion& Objeto::get_posicion() const{
	return posicion;
}

void Objeto::resize_all(double new_size){
	resize(new_size);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->resize(new_size);
}

void Objeto::set_line_width() {
	base->property_line_width() = 4;
}