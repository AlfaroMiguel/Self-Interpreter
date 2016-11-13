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

void ControladorEventos::mover_morph(const std::string& morph, double x, double y){
	modelo->mover_morph(morph, x, y);
	com_server->enviar_nueva_posicion_morph(morph, x, y);
}

void ControladorEventos::abrir_vm(const std::string& lobby, const std::string& nombre_cliente){
	com_server->enviar_datos_cliente(lobby, nombre_cliente);
}

void ControladorEventos::inicializar(){
	com_server->inicializar();
}

void ControladorEventos::crear_morph(Glib::RefPtr<Morph> morph) {
	cont_vistas->dibujar_morph(morph);
}

void ControladorEventos::eliminar_morph(Glib::RefPtr<Morph> morph) {
	cont_vistas->eliminar_morph(morph);
}

void ControladorEventos::editar(){
	cont_vistas->editar();
}

bool ControladorEventos::button_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
		modelo->editar_morph(event->x, event->y);
		return true;
	}
	if((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		modelo->crear_morph_de_slot(event->x, event->y);
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
									 double x, double y, std::map<std::string, std::string> dic_slots){
	//decirle al server
}