#ifndef CONT_VISTAS_H
#define CONT_VISTAS_H


#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"
#include "ventana_cliente.h"
#include "cont_eventos.h"
class VentanaVM;
//class VentanaObjetos;
//class VentanaInicio;
//class VentanaEdicion;
class Morph;


class ControladorVistas{
 	public:
 		ControladorVistas(VentanaInicio* inicio, VentanaEdicion* edicion,
							VentanaObjetos* objetos, VentanaVM* ventana_principal,
							VentanaCliente* ventana_cliente);
  		~ControladorVistas();

  		void dibujar_morph(Glib::RefPtr<Morph>);
  		void editar();
  		void set_lobby(const std::string& id);
  		void iniciar();
  		void crear_vm();
  		void eliminar_morph(Glib::RefPtr<Morph> morph);
  		void set_control(ControladorEventos* cont_eventos);
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