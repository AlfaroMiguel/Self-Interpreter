#ifndef SLOT_H
#define SLOT_H

#include "representacion.h"

class Slot: public Representacion{
 public:
  	static Glib::RefPtr<Slot> create(double x, double y, Glib::ustring& nombre, Glib::ustring& );
  	Slot(double x, double y, Glib::ustring& nombre, Glib::ustring& valor);
 	~Slot();
  	bool esta_en_posicion(double x, double y);
  	void mover(double new_x, double new_y);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
 private:
  	Glib::ustring& valor;
};
#endif