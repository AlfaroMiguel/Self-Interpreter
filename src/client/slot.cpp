#include "slot.h"
#include "morph.h"
#include <iostream>
#define ALTO 23
#define ANCHO 200

Glib::RefPtr<Slot> Slot::create(const Posicion& pos,
								const Glib::ustring& nombre,
								const Glib::ustring& valor,
								Morph& parent_morph){
	return Glib::RefPtr<Slot>(new Slot(pos, nombre, valor, parent_morph));
}

bool Slot::on_create(Glib::ustring cadena_texto){
	texto->property_text() = cadena_texto;
	if (base->property_width() < (cadena_texto.raw().size())*10){
		parent_morph.resize((cadena_texto.raw().size()) * 10);
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
//
//Slot::Slot(const Slot&& otra): Representacion(otra.posicion, otra.nombre), valor(otra.valor){}
//
//Slot& Slot::operator=(const Slot&& otra){
//	valor = otra.valor;
//	return *this;
//}

bool Slot::esta_en_posicion(const Posicion& pos_comparar) const{
	Posicion pos_max(posicion.get_x()+ANCHO, posicion.get_y()+ALTO);
	return posicion < pos_comparar && pos_max > pos_comparar;
}

void Slot::mover(const Posicion& new_pos){
	actualizar_posicion(new_pos);
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