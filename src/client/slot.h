#ifndef SLOT_H
#define SLOT_H

#include "representacion.h"
#include "posicion.h"
class Slot: public Representacion{
 public:
  	static Glib::RefPtr<Slot> create(const Posicion& pos,
									 const Glib::ustring& nombre,
									 const Glib::ustring& valor,
									 Morph& parent_morph);
  	Slot(const Posicion& pos, const Glib::ustring& nombre,
		 const Glib::ustring& valor, Morph& parent_morph);
 	~Slot();

  	Slot(const Slot&& otra);
  	Slot& operator=(const Slot&& otra);

  	bool esta_en_posicion(const Posicion& pos) const;
  	void mover(const Posicion& new_pos);
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
	Glib::ustring& obtener_valor();
  	Glib::ustring& obtener_nombre();
  	void add_path(int id_padre);
  	bool move_path(const Posicion* pos);
 private:
  	Glib::ustring valor;
  	Glib::RefPtr<Goocanvas::Path> path;
  	int id_padre;
  	Slot(const Slot& otra) = delete;
  	Slot& operator=(const Slot& otra) = delete;

  	bool on_create(Glib::ustring cadena_texto);
  	void set_line_width();
};
#endif