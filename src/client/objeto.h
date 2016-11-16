#ifndef OBJETO_H
#define OBJETO_H

#include "representacion.h"
#include "slot.h"

class Objeto: public Representacion{
 public:
  	Objeto(double pos_x, double pos_y, const Glib::ustring& nombre);
  	static Glib::RefPtr<Objeto> create(double pos_x, double pos_y, const Glib::ustring& nombre);
  	~Objeto();

  	Objeto(Objeto&& otra);
  	Objeto& operator=(Objeto&& otra);

  	void agregar_slots(std::map<std::string, std::string> slots_a_agregar);
  	void mover(double new_x, double new_y);
  	bool esta_en_posicion(double x, double y);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
  	Glib::ustring obtener_valor_slot(double x, double y);
  	Glib::ustring obtener_nombre_slot(double x, double y);
  	bool objeto_en_posicion(double x, double y);
  	bool slot_en_posicion(double x, double y);
  	const std::string get_nombre();
  	void cambiar_posicion(double x, double y);
 private:
  	std::vector<Glib::RefPtr<Slot>> slots;

  	Objeto(const Objeto& otra) = delete;
  	Objeto& operator=(const Objeto& otra) = delete;
};
#endif
