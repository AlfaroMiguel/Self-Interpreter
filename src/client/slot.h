#ifndef SLOT_H
#define SLOT_H

#include "representacion.h"

class Slot: public Representacion{
 public:
  	static Glib::RefPtr<Slot> create(double x, double y, const Glib::ustring& nombre, const Glib::ustring& valor);
  	Slot(double x, double y, const Glib::ustring& nombre, const Glib::ustring& valor);
 	~Slot();

  	Slot(const Slot&& otra);
  	Slot& operator=(const Slot&& otra);

  	bool esta_en_posicion(double x, double y);
  	void mover(double new_x, double new_y);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
	Glib::ustring& obtener_valor();
  	Glib::ustring& obtener_nombre();
 private:
  	Glib::ustring valor;

  	Slot(const Slot& otra) = delete;
  	Slot& operator=(const Slot& otra) = delete;
};
#endif