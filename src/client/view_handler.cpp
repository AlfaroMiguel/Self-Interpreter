#include "view_handler.h"
#include "ventanaVM.h"
#include "morph.h"
#include "ventana_cliente.h"
#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"
#include <iostream>

ViewHandler::ViewHandler(VentanaInicio *inicio,
									 VentanaEdicion *edicion,
									 VentanaObjetos *objetos,
									VentanaVM* ppal, VentanaCliente* cliente): ventana_principal(ppal), ventana_inicio(inicio),
										ventana_edicion(edicion), ventana_objetos(objetos), ventana_cliente(cliente){}

ViewHandler::~ViewHandler() {}

void ViewHandler::dibujar_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->dibujar_morph(morph);
}

void ViewHandler::eliminar_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->eliminar_morph(morph);
}

void ViewHandler::editar() {
	ventana_principal->editar();
}

void ViewHandler::ocultar_vista_cliente() {
	ventana_cliente->ocultar();
}

void ViewHandler::set_lobby(const std::string& id){
	ventana_inicio->set_lobby(id);
}

void ViewHandler::iniciar() {
	ventana_principal->inicializar();
}

void ViewHandler::crear_vm() {
	ventana_principal->iniciar();
}

void ViewHandler::set_control(ClientHandler *client_handler) {
	ventana_objetos->set_control(client_handler);
	ventana_inicio->set_control(client_handler);
	ventana_edicion->set_control(client_handler);
	ventana_cliente->set_control(client_handler);
	client_handler->set_control(this);
}

void ViewHandler::error_ingreso_cliente() {
	ventana_inicio->mostrar_error();
}