#ifndef MORPH_H
#define MORPH_H

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>

#include "objeto.h"
#include "slot.h"

class Morph: public Goocanvas::Group {
 public:
  	static Glib::RefPtr<Morph> create(double x, double y, const Glib::ustring& nombre);
  	Morph(double x, double y, const Glib::ustring& nombre);
  	~Morph();

  	Morph(Morph&& otra);
  	Morph& operator=(Morph&& otra);

  	void conectar_seniales();
  	void eliminar();
  	bool esta_en_posicion(double x, double y);
  	void editar_nombre(const std::string& nombre_nuevo);
  	void editando(bool valor);
  	bool editando();
  	void agregar_slots(std::map<std::string, std::string> slots_a_agregar);
  	double get_x();
  	double get_y();
  	void agregar_union(Glib::RefPtr<Goocanvas::Polyline> linea);
	const std::string& obtener_nombre_slot(double x, double y);
 protected:
  	Glib::RefPtr<Goocanvas::Item> dragging;
  	int drag_x, drag_y;
  	bool siendo_editado = false;
  	Glib::RefPtr<Objeto> objeto;
  	Glib::RefPtr<Goocanvas::Polyline> linea;

  	bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  	bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);
  	bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event);

 private:
  	Morph(const Morph& otra) = delete;
  	Morph& operator=(const Morph& otra) = delete;
};
#endif
