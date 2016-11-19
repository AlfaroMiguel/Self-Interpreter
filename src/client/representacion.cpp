#include "representacion.h"

#define ALTO 23
#define ANCHO 200

bool Representacion::on_create(){
	double pos_x = posicion.get_x();
	double pos_y = posicion.get_y();
	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
	texto = Goocanvas::Text::create(nombre, pos_x+2, pos_y+2);
	base->property_fill_color().set_value("white");
	texto->property_fill_color().set_value("black");
	add_child(base);
	add_child(texto);
	return false;
}

Representacion::Representacion(const Posicion& pos, const Glib::ustring &nombre):
				posicion(std::move(pos)), nombre(nombre){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &Representacion::on_create));
//	double pos_x = posicion.get_x();
//	double pos_y = posicion.get_y();
//	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
//	texto = Goocanvas::Text::create(nombre, pos_x+2, pos_y+2);
//	base->property_fill_color().set_value("white");
//	texto->property_fill_color().set_value("black");
//	add_child(base);
//	add_child(texto);
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

void Representacion::actualizar_posicion(const Posicion& new_pos){
	posicion += new_pos;
}

double Representacion::get_x() {
	return posicion.get_x();
}

double Representacion::get_y() {
	return posicion.get_y();
}
