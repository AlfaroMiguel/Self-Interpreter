#include "cont_eventos.h"

#include "modelo.h"
#include "comunicador_server.h"
#include "ventana_inicio.h"
#include "cont_vistas.h"

#include <iostream>
ControladorEventos::ControladorEventos(Modelo* modelo, ComunicadorServer* com_server): modelo(modelo),
																		 com_server(com_server) {}

ControladorEventos::~ControladorEventos() {}

void ControladorEventos::set_lobby(const std::string& id){
	cont_vistas->set_lobby(id);
}

void ControladorEventos::iniciar(){
	cont_vistas->iniciar();
}

void ControladorEventos::crear_vm(){
	//aca creo todos los morphs, hay que decirle al modelo
	cont_vistas->crear_vm();
}

void ControladorEventos::mover_morph(const std::string& morph, const Posicion& new_pos){
	modelo->mover_morph(morph, new_pos);
}

void ControladorEventos::actualizar_posicion(const std::string& morph, const Posicion& pos){
	com_server->enviar_nueva_posicion_morph(morph, pos);
}

void ControladorEventos::abrir_vm(const std::string& lobby, const std::string& estado_lobby){
	com_server->enviar_datos_cliente(lobby, estado_lobby);
}

void ControladorEventos::ingresar_cliente(const std::string &nombre_cliente) {
	com_server->ingresar_cliente(nombre_cliente);
}

void ControladorEventos::eliminar_morph(Glib::RefPtr<Morph> morph) {
	cont_vistas->eliminar_morph(morph);
}

void ControladorEventos::editar(){
	cont_vistas->editar();
}

bool ControladorEventos::button_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
//		double x = event->x;
//		double y = event->y;
		Posicion pos_evento(event->x, event->y);
		modelo->seleccionar_morph(pos_evento);
		if (modelo->es_objeto(pos_evento)) {
			std::cout << "Encuentra objeto" << std::endl;
			modelo->editar_morph();
		}
		if (modelo->es_slot(pos_evento)) {
			std::cout << "Encuentra slot" << std::endl;
			modelo->crear_morph_de_slot(pos_evento);
		}
		return true;
	}
	return false;
}

void ControladorEventos::cambio_nombre(const std::string& nuevo_nombre){
	modelo->cambiar_nombre_morph(nuevo_nombre);
}

void ControladorEventos::finalizar_edicion() {
	modelo->finalizar_edicion();
}

void ControladorEventos::eliminar_morph(double x, double y){
	modelo->eliminar_morph(x, y);
}

void ControladorEventos::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	if (mensaje.empty()) return;
	com_server->enviar_mensaje(mensaje, evento);
}

void ControladorEventos::set_control(ControladorVistas* contr_vistas) {
	this->cont_vistas = contr_vistas;
}

void ControladorEventos::crear_morph(const std::string& nombre,
									 const Posicion& pos, std::map<std::string, std::string> dic_slots){
	modelo->crear_morph(nombre, pos, dic_slots);
}

void ControladorEventos::crear_morph(const std::string& nombre, const Posicion& pos) {
	com_server->enviar_datos_morph(nombre, pos);
}

void ControladorEventos::dibujar_morph(Glib::RefPtr<Morph> morph){
	cont_vistas->dibujar_morph(morph);
}

void ControladorEventos::cambiar_pos_morph(const std::string& nombre, Posicion* pos){
	modelo->cambiar_pos_morph(nombre, pos);
}

void ControladorEventos::error_ingreso_cliente() {
	cont_vistas->error_ingreso_cliente();
}

void ControladorEventos::cliente_conectado(){
	com_server->inicializar();
	cont_vistas->ocultar_vista_cliente();
}