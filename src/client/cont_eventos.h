#ifndef CONT_EVENTOS_H
#define CONT_EVENTOS_H

#include <string>
#include <map>
#include <gtkmm.h>
#include "morph.h"
#include "comunicador_server.h"
#include "posicion.h"
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
  		void mover_morph(const std::string& morph, const Posicion& new_pos);
  		void actualizar_posicion(const std::string& morph, const Posicion& pos);
  		void abrir_vm(const std::string& lobby, const std::string& nombre_cliente);
  		void editar();
  		void crear_morph(const std::string& nombre, const Posicion& pos, std::map<std::string, std::string> dic_slots);
  		void crear_morph(const std::string& nombre, const Posicion& pos);
  		void dibujar_morph(Glib::RefPtr<Morph> morph);
  		bool button_event(GdkEventButton *event);
  		void cambio_nombre(const std::string& nuevo_nombre);
  		void finalizar_edicion();
  		void eliminar_morph(double x, double y);
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void enviar_mensaje(const std::string& mensaje, const std::string& evento);
		void ingresar_cliente(const std::string& nombre_cliente);
  		void mostrar_lobbies();
  		void cambiar_pos_morph(const std::string& nombre, Posicion* pos);
  		void error_ingreso_cliente();
  		void cliente_conectado();
 	private:
  		Modelo* modelo;
  		ComunicadorServer* com_server;
  		ControladorVistas* cont_vistas;
};
#endif