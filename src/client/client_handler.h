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
  		void add_lobby(const std::string& lobby_id);
  		/* Establece los lobbies que se mostraran al
  		 * usuario para que elija cual usar */
  		void set_lobbies();
  		/* Muestra el lobby seleccionado por el cliente */
  		void open_lobby();
  		/* Mueve el morph a la posicion indicada */
  		void move_morph(int morph_id, const Posicion& new_pos);
  		/* Actualiza la posicion del morph */
  		void update_morph_position(int morph_id, const Posicion& pos);
  		void abrir_vm(const std::string& lobby, const std::string& nombre_cliente);
  		/* Habilita la edicion del morph seleccionado */
  		void enable_editing();
  		/* Crea un morph nuevo */
  		void create_morph(const std::string& name, const Posicion& pos,
						 std::map<std::string, std::string> slots, int id);
  		/* Dibuja el morph en la interfaz */
  		void draw_morph(Glib::RefPtr<Morph> morph);
  		/* Elimina el morph editado de la interfaz */
  		void dismiss_morph();
  		bool button_event(GdkEventButton *event);
  		void cambio_nombre(const std::string& nuevo_nombre);
  		void finalizar_edicion();
  		void dismiss_morph(Glib::RefPtr<Morph> morph);
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