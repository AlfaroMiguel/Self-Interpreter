#ifndef OBJETO_H
#define OBJETO_H

#include "representacion.h"
#include "slot.h"
#include "posicion.h"

class Objeto: public Representacion{
 public:
  	Objeto(const Posicion& pos, const Glib::ustring& nombre);
  	static Glib::RefPtr<Objeto> create(const Posicion& pos, const Glib::ustring& nombre);
  	~Objeto();

  	Objeto(Objeto&& otra);
  	Objeto& operator=(Objeto&& otra);

  	void agregar_slots(std::map<std::string, std::string> slots_a_agregar);
  	void mover(double new_x, double new_y);
  	bool esta_en_posicion(const Posicion& pos_comparar) const;
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
  	Glib::ustring obtener_valor_slot(const Posicion& pos) const;
  	Glib::ustring obtener_nombre_slot(const Posicion& pos) const;
  	bool objeto_en_posicion(const Posicion& pos_comparar) const;
  	bool slot_en_posicion(const Posicion& pos_comparar) const;
  	const std::string get_nombre();
  	void cambiar_posicion(Posicion* pos);
 private:
  	std::vector<Glib::RefPtr<Slot>> slots;

  	Objeto(const Objeto& otra) = delete;
  	Objeto& operator=(const Objeto& otra) = delete;

  	bool on_cambiar_posicion(Posicion* pos);
};
#endif
