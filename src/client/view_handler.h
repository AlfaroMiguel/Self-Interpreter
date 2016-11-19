#ifndef VIEW_HANDLER_H
#define VIEW_HANDLER_H

#include "client_handler.h"

class VentanaVM;
class VentanaObjetos;
class VentanaInicio;
class VentanaEdicion;
class VentanaCliente;
class Morph;


class ViewHandler{
 	public:
 		ViewHandler(VentanaInicio* inicio, VentanaEdicion* edicion,
							VentanaObjetos* objetos, VentanaVM* ventana_principal,
							VentanaCliente* ventana_cliente);
  		~ViewHandler();

  		void dibujar_morph(Glib::RefPtr<Morph>);
  		void editar();
  		void set_lobby(const std::string& id);
  		void iniciar();
  		void crear_vm();
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void set_control(ClientHandler* client_handler);
		void mostrar_lobbies();
  		void error_ingreso_cliente();
  		void ocultar_vista_cliente();
 	private:
  		VentanaVM* ventana_principal;
  		VentanaInicio* ventana_inicio;
  		VentanaEdicion* ventana_edicion;
  		VentanaObjetos* ventana_objetos;
  		VentanaCliente* ventana_cliente;
};

#endif