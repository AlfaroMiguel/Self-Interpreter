#include "modelo.h"
#include "cont_vistas.h"
#include "morph.h"

Modelo::Modelo() {}

Modelo::~Modelo() {}

Modelo::Modelo(Modelo&& otra): morphs(otra.morphs), morph_editando(otra.morph_editando) {
}

Modelo& Modelo::operator=(Modelo&& otra){
	morphs = otra.morphs;
	morph_editando = otra.morph_editando;
	return *this;
}

bool Modelo::editar_morph(double x, double y){
	for(unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->esta_en_posicion(x, y)) {
			morphs[i]->editando(true);
			morph_editando = morphs[i];
			cont_eventos->editar();
			return true;
		}
	}
	return false;
}

void Modelo::cambiar_nombre_morph(const std::string& nuevo_nombre){
	if(morph_editando) morph_editando->editar_nombre(nuevo_nombre);
}

void Modelo::finalizar_edicion(){
	if (morph_editando) morph_editando->editando(false);
}

void Modelo::eliminar_morph(double x, double y){
	if (morph_editando){
		cont_eventos->eliminar_morph(morph_editando);
		for(unsigned int i = 0; i < morphs.size(); i++){
			if (morphs[i] == morph_editando)
				morphs.erase(morphs.begin()+i);
		}
	}
}

void Modelo::crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots) {
	const Glib::ustring nombre_morph(nombre);
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre_morph);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(dic_slots);
	morph->set_control(cont_eventos);
	cont_eventos->crear_morph(morph);
}

void Modelo::unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2) {
	double x_inicio = morph1->get_x();
	double x_fin = morph2->get_x();
	double y_inicio = morph1->get_y();
	double y_fin = morph2->get_y();
	Glib::RefPtr <Goocanvas::Polyline> linea = Goocanvas::Polyline::create(x_inicio, y_inicio, x_fin, y_fin);
	morph1->agregar_union(linea);
	morph2->agregar_union(linea);
}

void Modelo::crear_morph_de_slot(double x, double y){
	if (morph_editando){
		std::map<std::string, std::string> dic_slots;
		const std::string nombre = morph_editando->obtener_nombre_slot(x, y);
		if (! nombre.empty())
			crear_morph(nombre, x + 50, y + 50, dic_slots);
	}
}

void Modelo::mover_morph(const std::string& morph, double x, double y){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_nombre() == morph){
			morphs[i]->mover(x, y);
		}
	}
}

void Modelo::set_control(ControladorEventos *cont_eventos) {
	this->cont_eventos = cont_eventos;
}