#ifndef MORPH_H
#define MORPH_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>

#include "objeto.h"
#include "slot.h"

class Modelo;
class ClientHandler;

class Morph: public Goocanvas::Group {
 public:
  	static Glib::RefPtr<Morph> create(const Posicion& pos,
									  const Glib::ustring& nombre, int id);
  	Morph(const Posicion& pos, const Glib::ustring& nombre, int id);
  	~Morph();

  	Morph(Morph&& otra);
  	Morph& operator=(Morph&& otra);

  	void conectar_seniales();
  	/* Elimina al morph de la interfaz */
  	void dismiss();
  	bool esta_en_posicion(const Posicion& pos) const;
  	void editar_nombre(const std::string& nombre_nuevo);
  	void editando(bool valor);
  	bool editando();
  	void agregar_slots(std::map<std::string, std::string> slots_a_agregar);
  	double get_x() const;
  	double get_y() const;
  	int get_id() const;
  	const std::string get_nombre() const;
  	void agregar_union(Glib::RefPtr<Goocanvas::Polyline> linea);
	const std::string obtener_valor_slot(const Posicion& pos) const;
  	const std::string obtener_nombre_slot(const Posicion& pos) const;
  	void mover(const Posicion& new_pos);
  	void set_control(ClientHandler* client_handler);
  	bool es_objeto(const Posicion& pos) const;
  	bool es_slot(const Posicion& pos) const;
  	void cambiar_posicion(const Posicion& pos);
  	const Posicion& get_posicion() const;
  	bool has_id(int id);
  	void resize(double new_size);
  	void add_path_to_object(int id_padre, const std::string& slot_name);
  	void add_path_to_slot(const std::string& slot_name, int id_padre);
  	const Posicion& get_posicion_slot(const std::string& slot_name);
  	void move_path(const Posicion& pos_slot, int id_padre);
  	void add_union(int id, int id_padre, const std::string& slot_name);
  	bool shares_parent(int parent_id, const std::string& slot_name);
 private:
  	Glib::RefPtr<Goocanvas::Item> dragging;
  	int drag_x, drag_y;
  	bool siendo_editado = false;
  	Glib::RefPtr<Objeto> objeto;
  	//Glib::RefPtr<Goocanvas::Polyline> linea;
	int id;
  	ClientHandler* client_handler;

  	bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item,
									GdkEventButton* event);
  	bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item,
									  GdkEventButton* event);
  	bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item,
									 GdkEventMotion* event);

  	Morph(const Morph& otra) = delete;
  	Morph& operator=(const Morph& otra) = delete;

  	bool on_create(Glib::RefPtr<Objeto>);
  	bool do_dismiss();
};
#endif
