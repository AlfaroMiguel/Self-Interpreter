#ifndef OBJETO_H
#define OBJETO_H

#include "representacion.h"
#include "slot.h"
#include "posicion.h"
#include <mutex>

class Objeto: public Representacion{
 public:
  	Objeto(const Posicion& pos, const Glib::ustring& nombre,
		   Morph& parent_morph);
  	static Glib::RefPtr<Objeto> create(const Posicion& pos,
									   const Glib::ustring& nombre,
									   Morph& parent_morph);
  	~Objeto();

  	Objeto(Objeto&& otra);
  	Objeto& operator=(Objeto&& otra);

  	void agregar_slots(std::map<std::string, std::string> slots_a_agregar);
  	void mover(const Posicion& nueva_pos);
  	bool esta_en_posicion(const Posicion& pos_comparar) const;
  	void editar_nombre(const Glib::ustring& nombre_nuevo);
  	Glib::ustring obtener_valor_slot(const Posicion& pos) const;
  	Glib::ustring obtener_nombre_slot(const Posicion& pos) const;
  	bool objeto_en_posicion(const Posicion& pos_comparar) const;
  	bool slot_en_posicion(const Posicion& pos_comparar) const;
  	const std::string get_nombre();
  	void cambiar_posicion(const Posicion& pos);
  	const Posicion& get_posicion() const;
  	void resize_all(double new_size);
  	void add_path(int id_padre, const std::string& slot_name);
  	void add_path_to_slot(const std::string& slot_name, int id_padre);
  	const Posicion& get_posicion_slot(const std::string& slot_name);
  	void move_path();
  	bool shares_parent(int parent_id, const std::string& slot_name);

 private:
  	std::mutex mutex;
  	std::vector<Glib::RefPtr<Slot>> slots;
	//std::vector<Glib::RefPtr<Goocanvas::Path>> paths;
	int cant_paths = 0;
  	Objeto(const Objeto& otra) = delete;
  	Objeto& operator=(const Objeto& otra) = delete;

  	std::string name_slot;
  	int id_padre;

  	bool on_cambiar_posicion(const Posicion* pos);
  	bool on_mover(const Posicion* pos);
  	bool on_agregar_slot(Glib::RefPtr<Slot> slot);
  	void set_line_width();
  	bool on_add_path(Glib::RefPtr<Goocanvas::Path> path);
};
#endif
