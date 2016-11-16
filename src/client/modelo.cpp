#include "modelo.h"
#include "cont_vistas.h"
#include "morph.h"

Modelo::Modelo() {}

Modelo::~Modelo() {}

Modelo::Modelo(Modelo&& otra): morphs(otra.morphs), morph_editando(otra.morph_editando) {}

Modelo& Modelo::operator=(Modelo&& otra){
	morphs = otra.morphs;
	morph_editando = otra.morph_editando;
	return *this;
}

void Modelo::editar_morph(double x, double y){
	cont_eventos->editar();
}

void Modelo::seleccionar_morph(double x, double y){
	for(unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->esta_en_posicion(x, y)) {
			morphs[i]->editando(true);
			morph_editando = morphs[i];
		}
	}
}

void Modelo::cambiar_nombre_morph(const std::string& nuevo_nombre){
	if(morph_editando) morph_editando->editar_nombre(nuevo_nombre);
	std::cout << "Morphs: " << std::endl;
	for(unsigned int i = 0; i < morphs.size(); i++){
		std::cout << morphs[i]->get_nombre()  << std::endl;
	}
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

Glib::RefPtr<Morph> Modelo::crear_morph(const std::string& nombre, double x, double y, std::map<std::string, std::string> dic_slots) {
	std::cout << "Crea morph: " << nombre << std::endl;
	const Glib::ustring nombre_morph(nombre);
	Glib::RefPtr<Morph> morph = Morph::create(x, y, nombre_morph);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(dic_slots);
	morph->set_control(cont_eventos);
	cont_eventos->crear_morph(morph);
	return morph;
}

void Modelo::unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2, double x_inicio, double y_inicio) {
	double x_fin = morph2->get_x();
	double y_fin = morph2->get_y();
	Glib::RefPtr <Goocanvas::Polyline> linea = Goocanvas::Polyline::create(x_inicio, y_inicio, x_fin, y_fin);
	morph1->agregar_union(linea);
	morph2->agregar_union(linea);
}

void Modelo::crear_morph_de_slot(double x, double y){
	if (morph_editando){
		std::map<std::string, std::string> dic_slots;
		const std::string nombre(morph_editando->obtener_valor_slot(x, y));
		if (!nombre.empty() && !existe_morph(nombre)) {
			Glib::RefPtr <Morph> nuevo_morph = crear_morph(nombre, x + 50, y + 50, dic_slots);
			//unir_morphs(nuevo_morph, morph_editando, x, y);
		}
	}
}

void Modelo::mover_morph(const std::string& morph, double x, double y){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_nombre() == morph){
			morphs[i]->mover(x, y);
		}
	}
}

bool Modelo::existe_morph(const std::string& nombre){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_nombre() == nombre){
			return true;
		}
	}
	return false;
}
void Modelo::set_control(ControladorEventos *cont_eventos) {
	this->cont_eventos = cont_eventos;
}

void Modelo::inicializar(){

}

bool Modelo::es_objeto(double x, double y){
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->es_objeto(x, y))
			return true;
	return false;
}

bool Modelo::es_slot(double x, double y){
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->es_slot(x, y))
			return true;
	return false;
}