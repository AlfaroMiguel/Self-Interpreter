#ifndef MODELO_H
#define MODELO_H

#include "client_handler.h"
#include <gtkmm.h>
#include "union.h"
class Morph;

class Modelo{
 public:
  	Modelo();
  	~Modelo();

  	Modelo(Modelo&& otra);
  	Modelo& operator=(Modelo&& otra);

  	/* Crea un nuevo morph */
  	void create_morph(const std::string& name, const Posicion& pos,
					  std::map<std::string, std::string> slots, int id,
					  int id_padre, const std::string& slot_name);
  	/* Elimina el morph editado de la vista */
  	void dismiss_morph();
  	void dismiss_morph(int id);
  	void finalizar_edicion();
  	void cambiar_nombre_morph(const std::string& nuevo_nombre);
  	void editar_morph() const;
  	void unir_morphs(const Posicion& pos_begin, const Posicion& pos_end);
	void get_morph_from_slot(Posicion& pos);
  	/* Mueve el morph a la posicion indicada */
  	void move_morph(int morph_id, const Posicion& new_pos);
	void set_control(ClientHandler* client_handler);
  	bool es_objeto(const Posicion& pos) const;
  	bool es_slot(const Posicion& pos) const;
  	void seleccionar_morph(const Posicion& pos);
  	bool existe_morph(int morph_id);
  	void change_morph_position(int morph_id, const Posicion& new_pos);
  	Glib::RefPtr<Morph> get_selected_morph() const;
  	void reset_lobby();
  	void add_union(int id_obj, int id_padre, const std::string& slot_name);
 private:
  	Modelo(const Modelo& otra) = delete;
  	Modelo& operator=(const Modelo& otra) = delete;
	ClientHandler* client_handler;

  	std::vector<Glib::RefPtr<Morph>> morphs;
  	std::vector<Union*> unions;
  	Glib::RefPtr<Morph> selected_morph;
};
#endif
