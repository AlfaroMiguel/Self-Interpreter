#include "representacion.h"

#define ALTO 23
#define ANCHO 200

Representacion::Representacion(double pos_x, double pos_y, Glib::ustring &nombre):
				pos_x(pos_x), pos_y(pos_y), nombre(nombre){
	//create(pos_x, pos_y, ANCHO, ALTO);
	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
	base->property_fill_color().set_value("white");
	add_child(base);
}

Representacion::~Representacion() {}

void Representacion::actualizar_posicion(double new_x, double new_y){
	pos_x += new_x;
	pos_y += new_y;
}