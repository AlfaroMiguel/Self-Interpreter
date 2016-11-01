#include "representacion.h"

#define ALTO 23
#define ANCHO 200

Representacion::Representacion(double pos_x, double pos_y, const Glib::ustring &nombre):
				pos_x(pos_x), pos_y(pos_y), nombre(nombre){
	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
	texto = Goocanvas::Text::create(nombre, pos_x+2, pos_y+2);
	base->property_fill_color().set_value("white");
	texto->property_fill_color().set_value("black");
	add_child(base);
	add_child(texto);
}

Representacion::~Representacion() {}

Representacion::Representacion(const Representacion&& otra): pos_x(otra.pos_x), pos_y(otra.pos_y),
															 nombre(otra.nombre), base(otra.base),
															texto(otra.texto){}

Representacion& Representacion::operator=(const Representacion&& otra){
	pos_x = otra.pos_x;
	pos_y = otra.pos_y;
	nombre = otra.nombre;
	base = otra.base;
	texto = otra.texto;
	return *this;
}

void Representacion::actualizar_posicion(double new_x, double new_y){
	pos_x += new_x;
	pos_y += new_y;
}