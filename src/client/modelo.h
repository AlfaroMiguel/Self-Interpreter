#ifndef MODELO_H
#define MODELO_H

#include "cont_eventos.h"
#include "comunicador_server.h"
#include <gtkmm.h>
#include <goocanvasmm.h>

class ControladorVistas;
class Morph;

class Modelo{
 public:
  	Modelo();
  	~Modelo();

  	Modelo(Modelo&& otra);
  	Modelo& operator=(Modelo&& otra);

  	Glib::RefPtr<Morph> crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots);
  	void eliminar_morph(double x, double y);
  	void finalizar_edicion();
  	void cambiar_nombre_morph(const std::string& nuevo_nombre);
  	void editar_morph(double x, double y);
  	void unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2);
	void crear_morph_de_slot(double x, double y);
  	void mover_morph(const std::string& morph, double x, double y);
	void set_control(ControladorEventos* cont_eventos);
	void inicializar();
  	bool es_objeto(double x, double y);
  	bool es_slot(double x, double y);
  	void seleccionar_morph(double x, double y);
 private:
  	Modelo(const Modelo& otra) = delete;
  	Modelo& operator=(const Modelo& otra) = delete;
	ControladorEventos* cont_eventos;

  	std::vector<Glib::RefPtr<Morph>> morphs;
  	Glib::RefPtr<Morph> morph_editando;
};
#endif
