#include "cont_vistas.h"
#include "ventanaVM.h"
#include "morph.h"

#include <iostream>

ControladorVistas::ControladorVistas(VentanaInicio *inicio,
									 VentanaEdicion *edicion,
									 VentanaObjetos *objetos,
									VentanaVM* ppal): ventana_principal(ppal), ventana_inicio(inicio),
										ventana_edicion(edicion), ventana_objetos(objetos){}

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

void ControladorVistas::set_lobby(const std::string& id){
	ventana_inicio->set_lobby(id);
}

void ControladorVistas::iniciar() {
	ventana_inicio->iniciar();
}

void ControladorVistas::crear_vm() {
	ventana_principal->iniciar();
}

void ControladorVistas::set_control(ControladorEventos *cont_eventos) {
	ventana_objetos->set_control(cont_eventos);
	ventana_inicio->set_control(cont_eventos);
	ventana_edicion->set_control(cont_eventos);
	cont_eventos->set_control(this);
}