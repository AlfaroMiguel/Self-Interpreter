#ifndef REPRESENTACION_H
#define REPRESENTACION_H
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>

#include "posicion.h"

class Representacion: public Goocanvas::Group {
 public:
  	Representacion(const Posicion& pos, const Glib::ustring& nombre);
  	virtual ~Representacion();

  	Representacion(const Representacion&& otra);
  	Representacion& operator=(const Representacion&& otra);

  	virtual bool esta_en_posicion(const Posicion& pos_comparar) const = 0;
  	virtual void editar_nombre(const Glib::ustring& nombre_nuevo) = 0;
  	void actualizar_posicion(const Posicion& new_pos);

  	double get_x();
  	double get_y();
 protected:
  	Posicion posicion;
  	Glib::ustring nombre;
  	Glib::RefPtr<Goocanvas::Rect> base;
  	Glib::RefPtr<Goocanvas::Text> texto;
 private:
  	Representacion(const Representacion& otra) = delete;
  	Representacion& operator=(const Representacion& otra) = delete;

};
#endif
