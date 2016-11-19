#include "slot.h"
#include <iostream>
#define ALTO 23
#define ANCHO 200

Glib::RefPtr<Slot> Slot::create(const Posicion& pos, const Glib::ustring& nombre, const Glib::ustring& valor){
	return Glib::RefPtr<Slot>(new Slot(pos, nombre, valor));
}

bool Slot::on_create(Glib::ustring cadena_texto){
	texto->property_text() = cadena_texto;
	return false;
}
Slot::Slot(const Posicion& pos, const Glib::ustring& nombre, const Glib::ustring& valor):
			Representacion(pos, nombre), valor(valor){
	Glib::ustring cadena_texto = nombre + ": " + valor;
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Slot::on_create), cadena_texto));
}

Slot::~Slot(){}

Slot::Slot(const Slot&& otra): Representacion(otra.posicion, otra.nombre), valor(otra.valor){}

Slot& Slot::operator=(const Slot&& otra){
	valor = otra.valor;
	return *this;
}

bool Slot::esta_en_posicion(const Posicion& pos_comparar) const{
	Posicion pos_max(posicion.get_x()+ANCHO, posicion.get_y()+ALTO);
	//return pos_x < x && pos_x + ANCHO > x  && pos_y < y && pos_y + ALTO > y;
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