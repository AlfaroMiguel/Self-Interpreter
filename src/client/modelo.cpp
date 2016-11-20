#include "modelo.h"
#include "morph.h"

Modelo::Modelo() {}

Modelo::~Modelo() {}

Modelo::Modelo(Modelo&& otra): morphs(otra.morphs), morph_editando(otra.morph_editando) {}

Modelo& Modelo::operator=(Modelo&& otra){
	morphs = otra.morphs;
	morph_editando = otra.morph_editando;
	return *this;
}

void Modelo::editar_morph() const{
	client_handler->enable_editing();
}

void Modelo::seleccionar_morph(const Posicion& pos){
	for(unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->esta_en_posicion(pos)) {
			morphs[i]->editando(true);
			morph_editando = morphs[i];
		}
	}
}

void Modelo::cambiar_nombre_morph(const std::string& nuevo_nombre){
	if(morph_editando) morph_editando->editar_nombre(nuevo_nombre);
	for(unsigned int i = 0; i < morphs.size(); i++){
		std::cout << morphs[i]->get_nombre()  << std::endl;
	}
}

void Modelo::finalizar_edicion(){
	if (morph_editando) morph_editando->editando(false);
}

void Modelo::eliminar_morph(double x, double y){
	if (morph_editando){
		client_handler->eliminar_morph(morph_editando);
		for(unsigned int i = 0; i < morphs.size(); i++){
			if (morphs[i] == morph_editando)
				morphs.erase(morphs.begin()+i);
		}
	}
}


Glib::RefPtr<Morph> Modelo::create_morph(const std::string& name,
										const Posicion& pos,
										std::map<std::string,
												 std::string> slots,
										int id) {
	const Glib::ustring morph_name(name);
	Glib::RefPtr<Morph> morph = Morph::create(pos, morph_name, id);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(slots);
	morph->set_control(client_handler);
	client_handler->dibujar_morph(morph);
	return morph;
}

void Modelo::unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2, double x_inicio, double y_inicio) {
	double x_fin = morph2->get_x();
	double y_fin = morph2->get_y();
	Glib::RefPtr <Goocanvas::Polyline> linea = Goocanvas::Polyline::create(x_inicio, y_inicio, x_fin, y_fin);
	morph1->agregar_union(linea);
	morph2->agregar_union(linea);
}

void Modelo::crear_morph_de_slot(Posicion& pos){
	if (morph_editando){
		const std::string slot_name(morph_editando->obtener_nombre_slot(pos));
		client_handler->get_morph_from_slot(morph_editando->get_id(), slot_name);
	}
}

void Modelo::cambiar_pos_morph(int morph_id, Posicion* pos){
	std::cout << "En modelo la posicion es: " << pos->get_x() << ", " << pos->get_y() << std::endl;
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_id() == morph_id){
			morphs[i]->cambiar_posicion(pos);
		}
	}
}

void Modelo::move_morph(int morph_id, const Posicion& new_pos){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_id() == morph_id){
			morphs[i]->mover(new_pos);
		}
	}
}

bool Modelo::existe_morph(int morph_id){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->get_id() == morph_id){
			return true;
		}
	}
	return false;
}
void Modelo::set_control(ClientHandler *client_handler) {
	this->client_handler = client_handler;
}

bool Modelo::es_objeto(const Posicion& pos) const{
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->es_objeto(pos))
			return true;
	return false;
}

bool Modelo::es_slot(const Posicion& pos) const{
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->es_slot(pos))
			return true;
	return false;
}
