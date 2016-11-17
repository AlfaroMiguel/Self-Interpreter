#include "representacion.h"
#include "cont_eventos.h"
#define ALTO 23
#define ANCHO 200

Representacion::Representacion(const Posicion& pos, const Glib::ustring &nombre):
				posicion(std::move(pos)), nombre(nombre){
	double pos_x = posicion.get_x();
	double pos_y = posicion.get_y();
	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
	texto = Goocanvas::Text::create(nombre, pos_x+2, pos_y+2);
	base->property_fill_color().set_value("white");
	texto->property_fill_color().set_value("black");
	add_child(base);
	add_child(texto);
}

Representacion::~Representacion() {}

Representacion::Representacion(const Representacion&& otra): posicion(std::move(otra.posicion)),
															 nombre(otra.nombre), base(otra.base),
															texto(otra.texto){}

Representacion& Representacion::operator=(const Representacion&& otra){
	posicion = std::move(otra.posicion);
	nombre = otra.nombre;
	base = otra.base;
	texto = otra.texto;
	return *this;
}

void Representacion::actualizar_posicion(double new_x, double new_y){
	posicion.add_x(new_x);
	posicion.add_y(new_y);
}

double Representacion::get_x() {
	return posicion.get_x();
}

double Representacion::get_y() {
	return posicion.get_y();
}
