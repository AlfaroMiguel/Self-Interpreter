#include "view_handler.h"
#include "main_view.h"
#include "morph.h"
#include "ventana_cliente.h"
#include "ventana_edicion.h"
#include "ventana_objetos.h"
#include "ventana_inicio.h"
#include <iostream>

ViewHandler::ViewHandler(VentanaInicio *inicio,
									 VentanaEdicion *edicion,
									 VentanaObjetos *objetos,
									MainView* main_view, VentanaCliente* cliente): main_view(main_view), ventana_inicio(inicio),
										ventana_edicion(edicion), ventana_objetos(objetos), ventana_cliente(cliente){}

ViewHandler::~ViewHandler() {}

void ViewHandler::draw_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->draw_morph(morph);
}

void ViewHandler::dismiss_morph(Glib::RefPtr<Morph> morph){
	ventana_objetos->dismiss_morph(morph);
}

void ViewHandler::enable_editing(Glib::RefPtr<Morph> morph) {
	ventana_edicion->start(morph->get_nombre());
}

void ViewHandler::ocultar_vista_cliente() {
	ventana_cliente->ocultar();
}

void ViewHandler::add_lobby(const std::string& lobby_id){
	ventana_inicio->add_lobby(lobby_id);
}

void ViewHandler::set_lobbies() {
	ventana_inicio->inicializar();
}

void ViewHandler::open_lobby() {
	ventana_objetos->start();
}

void ViewHandler::set_control(ClientHandler *client_handler) {
	ventana_objetos->set_control(client_handler);
	ventana_inicio->set_control(client_handler);
	ventana_edicion->set_control(client_handler);
	ventana_cliente->set_control(client_handler);
	client_handler->set_handler(this);
}

void ViewHandler::client_connection_error() {
	ventana_inicio->mostrar_error();
}

void ViewHandler::quit(){
	main_view->quit();
}