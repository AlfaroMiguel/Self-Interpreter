#include "posicion.h"

Posicion::Posicion(double x, double y): x(x), y(y) {}
Posicion::~Posicion() {}

Posicion::Posicion(const Posicion&& otra): x(otra.x), y(otra.y){}

Posicion& Posicion::operator=(const Posicion&& otra){
	x = otra.x;
	y = otra.y;
	return *this;
}

bool Posicion::operator==(const Posicion& otra) const{
	return (x == otra.x && y == otra.y);
}

bool Posicion::operator>(const Posicion& otra) const{
	return (x > otra.x && y > otra.y);
}

bool Posicion::operator<(const Posicion& otra) const{
	return (x < otra.x && y < otra.y);
}

double Posicion::get_y() const{
	return y;
}

double Posicion::get_x() const{
	return x;
}

Posicion& Posicion::operator+=(const Posicion& otra){
	x += otra.x;
	y += otra.y;
	return *this;
}
//void Posicion::add_x(double x) {
//	this->x += x;
//}
//
//void Posicion::add_y(double y) {
//	this->y += y;
//}

void Posicion::set_x(double x) {
	this->x = x;
}

void Posicion::set_y(double y) {
	this->y = y;
}