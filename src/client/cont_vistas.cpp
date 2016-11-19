#include "cont_vistas.h"
#include "ventanaVM.h"
#include "morph.h"
#include "ventana_cliente.h"
#include <iostream>

ControladorVistas::ControladorVistas(VentanaInicio *inicio,
									 VentanaEdicion *edicion,
									 VentanaObjetos *objetos,
									VentanaVM* ppal, VentanaCliente* cliente): ventana_principal(ppal), ventana_inicio(inicio),
										ventana_edicion(edicion), ventana_objetos(objetos), ventana_cliente(cliente){}

ControladorVistas::~ControladorVistas() {}

void ControladorVistas::dibujar_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->dibujar_morph(morph);
}

void ControladorVistas::eliminar_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->eliminar_morph(morph);
}

void ControladorVistas::editar() {
	ventana_principal->editar();
}

void ControladorVistas::ocultar_vista_cliente() {
	ventana_cliente->ocultar();
}

void ControladorVistas::set_lobby(const std::string& id){
	ventana_inicio->set_lobby(id);
}

void ControladorVistas::iniciar() {
	ventana_principal->inicializar();
}

void ControladorVistas::crear_vm() {
	ventana_principal->iniciar();
}

void ControladorVistas::set_control(ClientHandler *client_handler) {
	ventana_objetos->set_control(client_handler);
	ventana_inicio->set_control(client_handler);
	ventana_edicion->set_control(client_handler);
	ventana_cliente->set_control(client_handler);
	client_handler->set_control(this);
}

void ControladorVistas::error_ingreso_cliente() {
	ventana_inicio->mostrar_error();
}