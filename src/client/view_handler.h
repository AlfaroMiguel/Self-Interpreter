#ifndef VIEW_HANDLER_H
#define VIEW_HANDLER_H

#include "client_handler.h"

class MainView;
class VentanaObjetos;
class VentanaInicio;
class VentanaEdicion;
class VentanaCliente;
class Morph;


class ViewHandler{
 	public:
 		ViewHandler(VentanaInicio* inicio, VentanaEdicion* edicion,
							VentanaObjetos* objetos, MainView* main_view,
							VentanaCliente* ventana_cliente);
  		~ViewHandler();

  		/* Dibuja el morph en la interfaz */
  		void draw_morph(Glib::RefPtr<Morph>);
  		/* Habilita la edicion del morph seleccionado */
  		void enable_editing(Glib::RefPtr<Morph> morph);
  		/* Agrega un lobby a los lobbies en los que puede
   		* participar el cliente */
  		void add_lobby(const std::string& lobby_id);
  		/* Establece los lobbies que se mostraran al
  		 * usuario para que elija cual usar */
  		void set_lobbies();
  		/* Muestra el lobby seleccionado por el cliente */
  		void open_lobby();
  		/* Elimina el morph de la interfaz */
  		void dismiss_morph(Glib::RefPtr<Morph> morph);
  		void set_control(ClientHandler* client_handler);
		void mostrar_lobbies();
  		void client_connection_error();
  		void ocultar_vista_cliente();
 	private:
  		MainView* main_view;
  		VentanaInicio* ventana_inicio;
  		VentanaEdicion* ventana_edicion;
  		VentanaObjetos* ventana_objetos;
  		VentanaCliente* ventana_cliente;
};

#endif