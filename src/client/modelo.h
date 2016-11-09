#ifndef MODELO_H
#define MODELO_H

#include "comunicador_server.h"
#include "morph.h"
#include <gtkmm.h>
#include <goocanvasmm.h>

class VentanaObjetos;
class VentanaEdicion;
class VentanaInicio;
class VentanaVM;

class Modelo{
 public:
  	Modelo(const std::string& hostname, const std::string& puerto);
  	~Modelo();

  	Modelo(Modelo&& otra);
  	Modelo& operator=(Modelo&& otra);

  	void crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots);
  	void enviar_mensaje(const std::string& mensaje, const std::string& evento);
  	void eliminar_morph(double x, double y);
  	void finalizar_edicion();
  	void cambiar_nombre_morph(const std::string& nuevo_nombre);
  	bool editar_morph(double x, double y);
  	void set_vista_objetos(VentanaObjetos* vista);
  	void set_vista_editar(VentanaEdicion* vista);
  	void set_vista_inicio(VentanaInicio* vista);
  	void unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2);
	void crear_morph_de_slot(double x, double y);
  	void set_lobby(const std::string& cant_lobbies);
  	void inicializar();
  	void iniciar();
  	void abrir_vm(VentanaVM* ventana_vm, const std::string& lobby, const std::string& nombre_cliente);
  	void crear_vm();
 private:
  	Modelo(const Modelo& otra) = delete;
  	Modelo& operator=(const Modelo& otra) = delete;

  	std::vector<Glib::RefPtr<Morph>> morphs;
  	Glib::RefPtr<Morph> morph_editando;
  	//Glib::RefPtr<Morph> shell;
  	ComunicadorServer com_server;
  	VentanaObjetos* ventana_objetos;
  	VentanaEdicion* ventana_edicion;
  	VentanaInicio* ventana_inicio;
  	VentanaVM* ventana_vm;
};
#endif
