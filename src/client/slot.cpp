#include "slot.h"
#include "morph.h"
#include <iostream>
#define ALTO 23
#define ANCHO 200
#define WIDTH_PER_CHARACTER 10

Glib::RefPtr<Slot> Slot::create(const Posicion& pos,
								const Glib::ustring& nombre,
								const Glib::ustring& valor,
								Morph& parent_morph){
	return Glib::RefPtr<Slot>(new Slot(pos, nombre, valor, parent_morph));
}

bool Slot::on_create(Glib::ustring cadena_texto){
	texto->property_text() = cadena_texto;
	if (needs_resize(cadena_texto.raw().size()*WIDTH_PER_CHARACTER)){
		parent_morph.resize((cadena_texto.raw().size()) * WIDTH_PER_CHARACTER);
	}
	return false;
}

Slot::Slot(const Posicion& pos, const Glib::ustring& nombre,
		   const Glib::ustring& valor, Morph& parent_morph):
			Representacion(pos, nombre, parent_morph), valor(valor){
	Glib::ustring cadena_texto = nombre + ": " + valor;
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Slot::on_create), cadena_texto));
}

Slot::~Slot(){}

Slot::Slot(const Slot&& otra): Representacion(otra.posicion, otra.nombre, otra.parent_morph), valor(otra.valor){}

Slot& Slot::operator=(const Slot&& otra){
	valor = otra.valor;
	return *this;
}

bool Slot::esta_en_posicion(const Posicion& pos_comparar) const{
	Posicion pos_max(posicion.get_x()+ANCHO, posicion.get_y()+ALTO);
	return posicion < pos_comparar && pos_max > pos_comparar;
}

void Slot::mover(const Posicion& new_pos){
	actualizar_posicion(new_pos);
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Slot::move_path), &new_pos));
}

void Slot::editar_nombre(const Glib::ustring& nombre_nuevo){
	nombre = nombre_nuevo;
	Glib::ustring texto_nuevo = nombre + ": " + valor;
	texto->property_text() = texto_nuevo;
}

Glib::ustring& Slot::obtener_valor(){
	return valor;
}

Glib::ustring& Slot::obtener_nombre(){
	return nombre;
}

void Slot::set_line_width() {
	base->property_line_width() = 0.5;
}

void Slot::add_path(int id_padre) {
	this->id_padre = id_padre;
}

bool Slot::move_path(const Posicion* new_pos) {
	parent_morph.add_union(id_padre, parent_morph.get_id(), nombre);
	return false;
}