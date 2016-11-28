#include "representacion.h"
#include "morph.h"
#define ALTO 23
#define ANCHO 200
#define WIDTH_PER_CHARACTER 10

bool Representacion::on_create(){
	double pos_x = posicion.get_x();
	double pos_y = posicion.get_y();
	base = Goocanvas::Rect::create(pos_x, pos_y, ANCHO, ALTO);
	texto = Goocanvas::Text::create(nombre, pos_x+2, pos_y+2);
	base->property_fill_color().set_value("white");
	texto->property_fill_color().set_value("black");
	texto->property_font().set_value("monospace");
	set_line_width();
	add_child(base);
	add_child(texto);
	return false;
}

Representacion::Representacion(const Posicion& pos,
							   const Glib::ustring &nombre,
							   Morph& parent_morph):
				posicion(std::move(pos)), nombre(nombre),
				parent_morph(parent_morph){
	Glib::signal_idle().connect(sigc::mem_fun(*this, &Representacion::on_create));
}

Representacion::~Representacion() {}

Representacion::Representacion(const Representacion&& otra):
	posicion(std::move(otra.posicion)), nombre(otra.nombre), base(otra.base),
	texto(otra.texto), parent_morph(otra.parent_morph){}

Representacion& Representacion::operator=(const Representacion&& otra){
	posicion = std::move(otra.posicion);
	nombre = otra.nombre;
	base = otra.base;
	texto = otra.texto;
	parent_morph = std::move(otra.parent_morph);
	return *this;
}

void Representacion::actualizar_posicion(const Posicion& new_pos){
	posicion += new_pos;
}

double Representacion::get_x() const{
	return posicion.get_x();
}

double Representacion::get_y() const{
	return posicion.get_y();
}

const Posicion& Representacion::get_posicion() const{
	return posicion;
}

bool Representacion::needs_resize(double max_width) {
	return base->property_width() < max_width;
}

bool Representacion::do_resize(double new_size){
	base->property_width().set_value(new_size);
	return false;
}

void Representacion::resize(double new_size) {
	Glib::signal_idle().connect(sigc::bind(sigc::mem_fun(*this, &Representacion::do_resize), new_size));
}

const Glib::ustring& Representacion::get_nombre() const{
	return nombre;
}