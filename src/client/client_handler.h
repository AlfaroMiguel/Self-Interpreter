#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "morph.h"
#include "comunicador_server.h"
#include "posicion.h"

#include <string>
#include <map>
#include <gtkmm.h>

class ViewHandler;
class Modelo;

/* Clase que se encarga de manejar las interacciones entre el servidor
 * y las distintas clases del cliente */
class ClientHandler{
 	public:
  		ClientHandler(Modelo* modelo, ComunicadorServer* com_server);
  		~ClientHandler();

  		void set_control(ViewHandler* view_handler);
  		/* Agrega un lobby a los lobbies en los que puede
  		 * participar el cliente */
  		void set_lobby(const std::string& id); //esta funcion se tiene que llamar add_lobby
  		void iniciar();
  		void crear_vm();
  		void mover_morph(int morph_id, const Posicion& new_pos);
  		void actualizar_posicion(int morph_id, const Posicion& pos);
  		void abrir_vm(const std::string& lobby, const std::string& nombre_cliente);
  		void editar();
  		void crear_morph(const std::string& nombre, const Posicion& pos,
						 std::map<std::string, std::string> dic_slots, int id);
  		void dibujar_morph(Glib::RefPtr<Morph> morph);
  		bool button_event(GdkEventButton *event);
  		void cambio_nombre(const std::string& nuevo_nombre);
  		void finalizar_edicion();
  		void eliminar_morph(double x, double y);
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void enviar_mensaje(const std::string& mensaje, const std::string& evento);
		void ingresar_cliente(const std::string& nombre_cliente);
  		void mostrar_lobbies();
  		void cambiar_pos_morph(int morph_id, Posicion* pos);
  		void error_ingreso_cliente();
  		void cliente_conectado();
  		void get_morph_from_slot(int morph_id, const std::string& slot_name);
 	private:
  		Modelo* modelo;
  		ComunicadorServer* com_server;
  		ViewHandler* view_handler;
};
#endif