#include "morph_object.h"
#include "morph.h"
#define ALTO 23
#define ANCHO 200
#define WIDTH_PER_CHARACTER 10

MorphObject::MorphObject(const Posicion& pos, const Glib::ustring& nombre,
			   Morph& parent_morph):
	Representacion(pos, nombre, parent_morph){}

Glib::RefPtr<MorphObject> MorphObject::create(const Posicion& pos,
									const Glib::ustring& nombre,
									Morph& parent_morph){
	return Glib::RefPtr<MorphObject>(new MorphObject(pos, nombre, parent_morph));
}

MorphObject::~MorphObject(){}

MorphObject::MorphObject(MorphObject&& otra):
	Representacion(otra.posicion, otra.nombre, otra.parent_morph),
	slots(otra.slots){}

MorphObject& MorphObject::operator=(MorphObject&& otra){
	slots = otra.slots;
	return *this;
}

bool MorphObject::is_in_position(const Posicion& pos_comparar) const{
	if (in_position(pos_comparar)) return true;
	if (slot_in_position(pos_comparar)) return true;
	return false;
}

bool MorphObject::on_agregar_slot(Glib::RefPtr<Slot> slot){
	add_child(slot);
	return false;
}


void MorphObject::add_slots(std::map<std::string, std::string> slots_a_agregar){
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
		Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &MorphObject::on_agregar_slot), slot_nuevo));
		it++;
		slots_agregados++;
	}
}

void MorphObject::change_position(const Posicion& new_pos){
	double x = new_pos.get_x();
	double y = new_pos.get_y();
	double offset_x = x - posicion.get_x();
	double offset_y = y - posicion.get_y();
	posicion.set_x(x);
	posicion.set_y(y);
	move_path();
	translate(offset_x, offset_y);
	Posicion pos_slot(offset_x, offset_y);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(pos_slot);
}

bool MorphObject::on_mover(const Posicion* new_pos){
	double new_x = new_pos->get_x();
	double new_y = new_pos->get_y();
	translate(new_x, new_y);
	move_path();
	actualizar_posicion(*new_pos);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->mover(*new_pos);
	return false;
}

void MorphObject::move_path(){
	parent_morph.add_union(parent_morph.get_id(), id_padre, name_slot);
}

void MorphObject::move(const Posicion& new_pos){
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &MorphObject::on_mover), &new_pos));
}

void MorphObject::edit_name(const Glib::ustring& nombre_nuevo){
	nombre = nombre_nuevo;
	if (needs_resize(nombre.raw().size()*WIDTH_PER_CHARACTER))
		resize_all((nombre.raw().size())*WIDTH_PER_CHARACTER);
	texto->property_text() = nombre_nuevo;
}

Glib::ustring MorphObject::get_slot_value(const Posicion& pos) const{
	for (unsigned int i = 0; i < slots.size(); i++) {
		if (slots[i]->esta_en_posicion(pos))
			return slots[i]->obtener_valor();
	}
	Glib::ustring vacia;
	return vacia;
}

Glib::ustring MorphObject::get_slot_name(const Posicion& pos) const{
	for (unsigned int i = 0; i < slots.size(); i++) {
		if (slots[i]->esta_en_posicion(pos)) {
			return slots[i]->obtener_nombre();
		}
	}
	Glib::ustring vacia;
	return vacia;
}

const std::string MorphObject::get_name() {
	return nombre.raw();
}

bool MorphObject::in_position(const Posicion& pos_comparar) const {
	Posicion pos_max(posicion.get_x()+ANCHO, posicion.get_y()+ALTO);
	return posicion < pos_comparar && pos_max > pos_comparar;
}

bool MorphObject::slot_in_position(const Posicion& pos_comparar) const{
	for (unsigned int i = 0; i < slots.size(); i++)
		if (slots[i]->esta_en_posicion(pos_comparar)) return true;
	return false;
}

const Posicion& MorphObject::get_position() const{
	return posicion;
}

void MorphObject::resize_all(double new_size){
	resize(new_size);
	for (unsigned int i = 0; i < slots.size(); i++)
		slots[i]->resize(new_size);
}

void MorphObject::set_line_width() {
	base->property_line_width() = 4;
}

void MorphObject::add_path(int id_padre, const std::string& name_slot) {
	this->id_padre = id_padre;
	std::string name(name_slot.c_str());
	this->name_slot = name;
}

void MorphObject::add_path_to_slot(const std::string& slot_name, int id_padre) {
	for (unsigned int i = 0; i < slots.size(); i++)
		if (slots[i]->get_nombre().raw() == slot_name) {
			slots[i]->add_path(id_padre);
		}
}

const Posicion& MorphObject::get_slot_position(const std::string &slot_name) {
	for (unsigned int i = 0; i < slots.size(); i++)
		if (slots[i]->get_nombre().raw() == slot_name)
			return slots[i]->get_posicion();
}

bool MorphObject::shares_parent(int parent_id, const std::string& slot_name){
	return this->id_padre == parent_id && this->name_slot == slot_name;
}