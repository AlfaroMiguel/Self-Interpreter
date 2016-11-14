#ifndef CONT_EVENTOS_H
#define CONT_EVENTOS_H

#include <string>
#include <map>
#include <gtkmm.h>
#include "morph.h"
#include "comunicador_server.h"

class Modelo;
class ControladorVistas;

class ControladorEventos{
 	public:
  		ControladorEventos(Modelo* modelo, ComunicadorServer* com_server);
  		~ControladorEventos();

  		void set_control(ControladorVistas* cont_vistas);
  		void set_lobby(const std::string& id);
  		void iniciar();
  		void crear_vm();
  		void mover_morph(const std::string& morph, double x, double y);
  		void abrir_vm(const std::string& lobby, const std::string& nombre_cliente);
  		void inicializar();
  		void editar();
  		void crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots);
  		void crear_morph(Glib::RefPtr<Morph> morph);
  		bool button_event(GdkEventButton *event);
  		void cambio_nombre(const std::string& nuevo_nombre);
  		void finalizar_edicion();
  		void eliminar_morph(double x, double y);
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void enviar_mensaje(const std::string& mensaje, const std::string& evento);

 	private:
  		Modelo* modelo;
  		ComunicadorServer* com_server;
  		ControladorVistas* cont_vistas;
};
#endif