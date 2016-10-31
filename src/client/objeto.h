#ifndef OBJETO_H
#define OBJETO_H

#include "representacion.h"
#include "slot.h"
class Objeto: public Representacion{
 public:
  	Objeto(double pos_x, double pos_y, Glib::ustring& nombre);
  	static Glib::RefPtr<Objeto> create(double pos_x, double pos_y, Glib::ustring& nombre);
  	~Objeto();
  	void agregar_slots(std::map<Glib::ustring, Glib::ustring> slots_a_agregar);
  	void mover(double new_x, double new_y);
  	bool esta_en_posicion(double x, double y);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
 private:
  	std::vector<Glib::RefPtr<Slot>> slots;
};
#endif
