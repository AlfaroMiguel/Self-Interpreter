#ifndef SLOT_H
#define SLOT_H

#include "representacion.h"
#include "posicion.h"
class Slot: public Representacion{
 public:
  	static Glib::RefPtr<Slot> create(const Posicion& pos, const Glib::ustring& nombre, const Glib::ustring& valor);
  	Slot(const Posicion& pos, const Glib::ustring& nombre, const Glib::ustring& valor);
 	~Slot();

  	Slot(const Slot&& otra);
  	Slot& operator=(const Slot&& otra);

  	bool esta_en_posicion(const Posicion& pos) const;
  	void mover(const Posicion& new_pos);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
	Glib::ustring& obtener_valor();
  	Glib::ustring& obtener_nombre();
 private:
  	Glib::ustring valor;

  	Slot(const Slot& otra) = delete;
  	Slot& operator=(const Slot& otra) = delete;

  	bool on_create(Glib::ustring cadena_texto);
};
#endif