#include "client_handler.h"

#include "modelo.h"
#include "comunicador_server.h"
#include "ventana_inicio.h"
#include "cont_vistas.h"

#include <iostream>
ClientHandler::ClientHandler(Modelo* modelo, ComunicadorServer* com_server): modelo(modelo),
																		 com_server(com_server) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::set_lobby(const std::string& id){
	cont_vistas->set_lobby(id);
}

void ClientHandler::iniciar(){
	cont_vistas->iniciar();
}

void ClientHandler::crear_vm(){
	cont_vistas->crear_vm();
}

void ClientHandler::mover_morph(const std::string& morph, const Posicion& new_pos){
	modelo->mover_morph(morph, new_pos);
}

void ClientHandler::actualizar_posicion(int morph_id, const Posicion& pos){
	com_server->enviar_nueva_posicion_morph(morph_id, pos);
}

void ClientHandler::abrir_vm(const std::string& lobby, const std::string& estado_lobby){
	com_server->enviar_datos_cliente(lobby, estado_lobby);
}

void ClientHandler::ingresar_cliente(const std::string &nombre_cliente) {
	com_server->ingresar_cliente(nombre_cliente);
}

void ClientHandler::eliminar_morph(Glib::RefPtr<Morph> morph) {
	cont_vistas->eliminar_morph(morph);
}

void ClientHandler::editar(){
	cont_vistas->editar();
}

bool ClientHandler::button_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
		Posicion pos_evento(event->x, event->y);
		modelo->seleccionar_morph(pos_evento);
		if (modelo->es_objeto(pos_evento))
			modelo->editar_morph();
		if (modelo->es_slot(pos_evento))
			modelo->crear_morph_de_slot(pos_evento);
		return true;
	}
	return false;
}

void ClientHandler::cambio_nombre(const std::string& nuevo_nombre){
	modelo->cambiar_nombre_morph(nuevo_nombre);
}

void ClientHandler::finalizar_edicion() {
	modelo->finalizar_edicion();
}

void ClientHandler::eliminar_morph(double x, double y){
	modelo->eliminar_morph(x, y);
}

void ClientHandler::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	if (mensaje.empty()) return;
	com_server->enviar_mensaje(mensaje, evento);
}

void ClientHandler::set_control(ControladorVistas* contr_vistas) {
	this->cont_vistas = contr_vistas;
}

void ClientHandler::crear_morph(const std::string& nombre,
									 const Posicion& pos,
									 std::map<std::string,
											  std::string> dic_slots,
									 int id){
	modelo->crear_morph(nombre, pos, dic_slots, id);
}
//
//void ClientHandler::crear_morph(const std::string& nombre, const Posicion& pos) {
//	com_server->enviar_datos_morph(nombre, pos);
//}

void ClientHandler::dibujar_morph(Glib::RefPtr<Morph> morph){
	cont_vistas->dibujar_morph(morph);
}

void ClientHandler::cambiar_pos_morph(const std::string& nombre, Posicion* pos){
	std::cout << "En cambiar pos morph: " << pos->get_x() << ", " << pos->get_y() << std::endl;
	modelo->cambiar_pos_morph(nombre, pos);
}

void ClientHandler::error_ingreso_cliente() {
	cont_vistas->error_ingreso_cliente();
}

void ClientHandler::cliente_conectado(){
	com_server->inicializar();
	cont_vistas->ocultar_vista_cliente();
}

void ClientHandler::get_morph_from_slot(int morph_id, const std::string& slot_name) {
	com_server->get_morph_from_slot(morph_id, slot_name);
}