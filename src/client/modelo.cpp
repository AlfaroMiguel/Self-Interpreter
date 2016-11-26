#include "modelo.h"
#include "morph.h"

Modelo::Modelo() {}

Modelo::~Modelo() {}

Modelo::Modelo(Modelo&& otra): morphs(otra.morphs), selected_morph(otra.selected_morph) {}

Modelo& Modelo::operator=(Modelo&& otra){
	morphs = otra.morphs;
	selected_morph = otra.selected_morph;
	return *this;
}

void Modelo::editar_morph() const{
	client_handler->enable_editing(selected_morph);
}

void Modelo::seleccionar_morph(const Posicion& pos){
	for(unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->esta_en_posicion(pos)) {
			morphs[i]->editando(true);
			selected_morph = morphs[i];
		}
	}
}

Glib::RefPtr<Morph> Modelo::get_selected_morph() const {
	return selected_morph;
}

void Modelo::cambiar_nombre_morph(const std::string& new_name){
	if(selected_morph)
		selected_morph->editar_nombre(new_name);
}

void Modelo::finalizar_edicion(){
	if (selected_morph) selected_morph->editando(false);
}

void Modelo::dismiss_morph(){
	if (selected_morph){
		client_handler->dismiss_morph(selected_morph);
		for(unsigned int i = 0; i < morphs.size(); i++)
			if (morphs[i] == selected_morph)
				morphs.erase(morphs.begin()+i);
	}
}

Glib::RefPtr<Morph> Modelo::create_morph(const std::string& name,
										const Posicion& pos,
										std::map<std::string,
												 std::string> slots,
										int id) {
	for(unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->has_id(id)) {
			client_handler->dismiss_morph(morphs[i]);
			morphs.erase(morphs.begin()+i);
		}
	const Glib::ustring morph_name(name);
	Glib::RefPtr<Morph> morph = Morph::create(pos, morph_name, id);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(slots);
	morph->set_control(client_handler);
	client_handler->draw_morph(morph);
	return morph;
}

void Modelo::unir_morphs(Glib::RefPtr<Morph> morph1, Glib::RefPtr<Morph> morph2, double x_inicio, double y_inicio) {
	double x_fin = morph2->get_x();
	double y_fin = morph2->get_y();
	Glib::RefPtr <Goocanvas::Polyline> linea = Goocanvas::Polyline::create(x_inicio, y_inicio, x_fin, y_fin);
	morph1->agregar_union(linea);
	morph2->agregar_union(linea);
}

void Modelo::get_morph_from_slot(Posicion& pos){
	if (selected_morph){
		const std::string slot_name(selected_morph->obtener_nombre_slot(pos));
		client_handler->get_morph_from_slot(selected_morph->get_id(), slot_name);
	}
}

void Modelo::change_morph_position(int morph_id, const Posicion& new_pos){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(morph_id)){
			morphs[i]->cambiar_posicion(new_pos);
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
