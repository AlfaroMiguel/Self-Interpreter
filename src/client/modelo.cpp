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

void Modelo::create_morph(const std::string& name, const Posicion& pos,
						  std::map<std::string, std::string> slots, int id,
						  int id_padre, const std::string& slot_name) {
	for (unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->has_id(id)) {
			client_handler->hide_morph(morphs[i]);
			morphs.erase(morphs.begin() + i);
		}
	const Glib::ustring morph_name(name);
	Glib::RefPtr <Morph> morph = Morph::create(pos, morph_name, id);
	morphs.push_back(morph);
	morph->conectar_seniales();
	morph->agregar_slots(slots);
	morph->set_control(client_handler);
	morph->add_path_to_object(id_padre, slot_name);
	client_handler->draw_morph(morph);
	Union* morph_union = new Union(id, id_padre, slot_name, client_handler);
	bool existe = false;
	if (id_padre != 0) {
		for (unsigned int i = 0; i < morphs.size(); i++)
			if (morphs[i]->has_id(id_padre)) {
				for (unsigned int i = 0; i < unions.size(); ++i){
					if (*(unions[i]) == *(morph_union)){
						existe = true;
						break;
					}
				}
				if (! existe) {
					morph_union->add_path(morphs[i]->get_posicion_slot(slot_name), pos);
					morphs[i]->add_path_to_slot(slot_name, id);
					unions.push_back(morph_union);
				}
			}
	}
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
		if (morphs[i]->has_id(morph_id)){
			morphs[i]->mover(new_pos);
		}
	}
}

bool Modelo::existe_morph(int morph_id){
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(morph_id)){
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

void Modelo::reset_lobby() {
	for(unsigned int i = 0; i < morphs.size(); i++)
		client_handler->dismiss_morph(morphs[i]);
	morphs.clear();
}

void Modelo::dismiss_morph(int id) {
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(id)){
			client_handler->dismiss_morph(morphs[i]);
		}
	}
}

void Modelo::add_union(int id_obj, int id_padre, const std::string& slot_name){
	Posicion pos_begin(0,0);
	Posicion pos_end(0,0);
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(id_obj)){
			pos_begin.set_x(morphs[i]->get_posicion().get_x());
			pos_begin.set_y(morphs[i]->get_posicion().get_y());
		}
		if (morphs[i]->has_id(id_padre)){
			pos_end.set_x(morphs[i]->get_posicion_slot(slot_name).get_x());
			pos_end.set_y(morphs[i]->get_posicion_slot(slot_name).get_y());
		}
	}
	Union morph_union(id_obj, id_padre, slot_name, client_handler);
	for (unsigned int i = 0; i < unions.size(); ++i){
		if (*(unions[i]) == morph_union){
			unions[i]->update_path(pos_begin, pos_end);
		}
	}
}