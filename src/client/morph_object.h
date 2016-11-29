#ifndef OBJETO_H
#define OBJETO_H

#include "representacion.h"
#include "slot.h"
#include "posicion.h"

class MorphObject: public Representacion{
 public:
  	MorphObject(const Posicion& pos, const Glib::ustring& nombre,
		   Morph& parent_morph);
  	static Glib::RefPtr<MorphObject> create(const Posicion& pos,
									   const Glib::ustring& nombre,
									   Morph& parent_morph);
  	~MorphObject();

  	MorphObject(MorphObject&& otra);
  	MorphObject& operator=(MorphObject&& otra);

  	void add_slots(std::map<std::string, std::string> added_slots);
  	void move(const Posicion& new_pos);
  	bool is_in_position(const Posicion& pos_comparar) const;
  	void edit_name(const Glib::ustring& nombre_nuevo);
  	Glib::ustring get_slot_value(const Posicion& pos) const;
  	Glib::ustring get_slot_name(const Posicion& pos) const;
  	bool in_position(const Posicion& pos_comparar) const;
  	bool slot_in_position(const Posicion& pos_comparar) const;
  	const std::string get_name();
  	void change_position(const Posicion& pos);
  	const Posicion& get_position() const;
  	void resize_all(double new_size);
  	void add_path(int id_padre, const std::string& slot_name);
  	void add_path_to_slot(const std::string& slot_name, int id_padre);
  	const Posicion& get_slot_position(const std::string& slot_name);
  	void move_path();
  	bool shares_parent(int parent_id, const std::string& slot_name);

 private:
  	std::vector<Glib::RefPtr<Slot>> slots;
	int cant_paths = 0;
  	MorphObject(const MorphObject& otra) = delete;
  	MorphObject& operator=(const MorphObject& otra) = delete;

  	std::string name_slot;
  	int id_padre;

  	bool on_cambiar_posicion(const Posicion* pos);
  	bool on_mover(const Posicion* pos);
  	bool on_agregar_slot(Glib::RefPtr<Slot> slot);
  	void set_line_width();
  	bool on_add_path(Glib::RefPtr<Goocanvas::Path> path);
};
#endif
