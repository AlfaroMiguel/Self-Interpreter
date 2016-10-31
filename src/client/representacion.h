#ifndef REPRESENTACION_H
#define REPRESENTACION_H
#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>
#include <vector>
#include <map>


class Representacion: public Goocanvas::Group {
 public:
  	Representacion(double pos_x, double pos_y, Glib::ustring& nombre);
  	virtual ~Representacion();
  	virtual bool esta_en_posicion(double x, double y) = 0;
  	virtual void editar_nombre(const Glib::ustring& nombre_nuevo) = 0;
  	void actualizar_posicion(double new_x, double new_y);
 protected:
  	double pos_x, pos_y;
  	Glib::ustring nombre;
  	Glib::RefPtr<Goocanvas::Rect> base;
  	Glib::RefPtr<Goocanvas::Text> texto;
};
#endif
