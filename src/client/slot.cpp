#include "slot.h"

#define ALTO 23
#define ANCHO 200

Glib::RefPtr<Slot> Slot::create(double x, double y, Glib::ustring& nombre, Glib::ustring& valor){
	return Glib::RefPtr<Slot>(new Slot(x, y, nombre, valor));
}

Slot::Slot(double x, double y, Glib::ustring& nombre, Glib::ustring& valor):
			Representacion(x, y, nombre), valor(valor){
	Glib::ustring cadena_texto = nombre + ": " + valor;
	texto = Goocanvas::Text::create(cadena_texto, pos_x+2, pos_y+2);
	add_child(texto);
}

Slot::~Slot(){}

bool Slot::esta_en_posicion(double x, double y){
	return pos_x < x && pos_x + ANCHO > x  && pos_y < y && pos_y + ALTO > y;
}

void Slot::mover(double new_x, double new_y){
	actualizar_posicion(new_x, new_y);
}

void Slot::editar_nombre(const Glib::ustring& nombre_nuevo){
	nombre = nombre_nuevo;
	Glib::ustring texto_nuevo = nombre + ": " + valor;
	texto->property_text() = texto_nuevo;
}