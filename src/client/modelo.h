#ifndef MODELO_H
#define MODELO_H

#include "client_handler.h"
#include "comunicador_server.h"
#include <gtkmm.h>
#include <goocanvasmm.h>

class Morph;

class Modelo{
 public:
  	Modelo();
  	~Modelo();

  	Modelo(Modelo&& otra);
  	Modelo& operator=(Modelo&& otra);

  	Glib::RefPtr<Morph> crear_morph(const std::string& nombre,
									const Posicion& pos,
									std::map<std::string,
											 std::string> dic_slots,
									int id);
  	void eliminar_morph(double x, double y);
  	void finalizar_edicion();
  	void cambiar_nombre_morph(const std::string& nuevo_nombre);
  	void editar_morph() const;
  	void unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2, double x, double y);
	void crear_morph_de_slot(Posicion& pos);
  	void mover_morph(int morph_id, const Posicion& new_pos);
	void set_control(ClientHandler* client_handler);
  	bool es_objeto(const Posicion& pos) const;
  	bool es_slot(const Posicion& pos) const;
  	void seleccionar_morph(const Posicion& pos);
  	bool existe_morph(int morph_id);
  	void cambiar_pos_morph(int morph_id, Posicion* pos);
 private:
  	Modelo(const Modelo& otra) = delete;
  	Modelo& operator=(const Modelo& otra) = delete;
	ClientHandler* client_handler;

  	std::vector<Glib::RefPtr<Morph>> morphs;
  	Glib::RefPtr<Morph> morph_editando;
};
#endif
