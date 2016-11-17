#include "posicion.h"

Posicion::Posicion(double x, double y): x(x), y(y) {}

Posicion::~Posicion() {}

double Posicion::get_y() {
	return y;
}

double Posicion::get_x() {
	return x;
}

void Posicion::add_x(double x) {
	this->x += x;
}

void Posicion::add_y(double y) {
	this->y += y;
}