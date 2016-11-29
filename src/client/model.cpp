#include "model.h"
#include "morph.h"

Model::Model() {}

Model::~Model() {
	for (unsigned int i = 0; i < unions.size(); i++) {
		delete unions[i];
	}
}

Model::Model(Model &&otra) : morphs(otra.morphs),
							 selected_morph(otra.selected_morph) {}

Model &Model::operator=(Model &&otra) {
	morphs = otra.morphs;
	selected_morph = otra.selected_morph;
	return *this;
}

void Model::set_handler(ClientHandler *client_handler) {
	this->client_handler = client_handler;
}

void Model::create_morph(const std::string &name, const Posicion &pos,
						 std::map<std::string, std::string> slots, int id,
						 int parent_id, const std::string &slot_name) {
	for (unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->has_id(id)) {
			client_handler->hide_morph(morphs[i]);
			morphs.erase(morphs.begin() + i);
		}
	const Glib::ustring morph_name(name);
	Glib::RefPtr <Morph> morph = Morph::create(pos, morph_name, id);
	for (unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->shares_parent(parent_id, slot_name)) {
			client_handler->hide_morph(morphs[i]);
			morphs.erase(morphs.begin() + i);
		}
	}
	morphs.push_back(morph);
	morph->connect_signals();
	morph->add_slots(slots);
	morph->set_handler(client_handler);
	morph->add_path_to_object(parent_id, slot_name);
	client_handler->draw_morph(morph);
	Union *morph_union = new Union(id, parent_id, slot_name, client_handler);
	bool existing_union = false;
	if (parent_id != 0) {
		for (unsigned int i = 0; i < morphs.size(); i++)
			if (morphs[i]->has_id(parent_id)) {
				for (unsigned int i = 0; i < unions.size(); ++i) {
					if (*(unions[i]) == *(morph_union)) {
						existing_union = true;
						break;
					}
				}
				if (!existing_union) {
					morph_union->add_path
						(morphs[i]->get_slot_position(slot_name), pos);
					morphs[i]->add_path_to_slot(slot_name, id);
					unions.push_back(morph_union);
				}
			}
	}
}

void Model::dismiss_morph(int id) {
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(id)) {
			client_handler->dismiss_morph(morphs[i]);
		}
	}
}

void Model::dismiss_morph() {
	if (selected_morph) {
		client_handler->dismiss_morph(selected_morph);
		for (unsigned int i = 0; i < morphs.size(); i++)
			if (morphs[i] == selected_morph)
				morphs.erase(morphs.begin() + i);
	}
}

void Model::change_morph_name(const std::string &new_name) {
	if (selected_morph)
		selected_morph->edit_name(new_name);
}

void Model::enable_editing() const {
	client_handler->enable_editing(selected_morph);
}

void Model::get_morph_from_slot(Posicion &slot_pos) {
	for (unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->is_in_position(slot_pos)) {
			const std::string slot_name(morphs[i]->get_slot_name(slot_pos));
			client_handler->get_morph_from_slot(morphs[i]->get_id(),
												slot_name);
		}
	}
}

void Model::move_morph(int morph_id, const Posicion &new_pos) {
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(morph_id)) {
			morphs[i]->move(new_pos);
		}
	}
}

bool Model::is_object(const Posicion &pos) const {
	for (unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->is_object(pos))
			return true;
	return false;
}

bool Model::is_slot(const Posicion &pos) const {
	for (unsigned int i = 0; i < morphs.size(); i++)
		if (morphs[i]->is_slot(pos))
			return true;
	return false;
}

void Model::select_morph(const Posicion &morph_pos) {
	for (unsigned int i = 0; i < morphs.size(); i++) {
		if (morphs[i]->is_in_position(morph_pos))
			selected_morph = morphs[i];
	}
}

bool Model::existing_morph(int morph_id) {
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(morph_id)) {
			return true;
		}
	}
	return false;
}

void Model::change_morph_position(int morph_id, const Posicion &new_pos) {
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(morph_id)) {
			morphs[i]->change_position(new_pos);
		}
	}
}

Glib::RefPtr <Morph> Model::get_selected_morph() const {
	return selected_morph;
}

void Model::reset_lobby() {
	for (unsigned int i = 0; i < morphs.size(); i++)
		client_handler->dismiss_morph(morphs[i]);
	morphs.clear();
}

void Model::add_union(int id_obj, int parent_id, const std::string &slot_name) {
	Posicion pos_begin(0, 0);
	Posicion pos_end(0, 0);
	for (unsigned int i = 0; i < morphs.size(); ++i) {
		if (morphs[i]->has_id(id_obj)) {
			pos_begin.set_x(morphs[i]->get_position().get_x());
			pos_begin.set_y(morphs[i]->get_position().get_y());
		}
		if (morphs[i]->has_id(parent_id)) {
			pos_end.set_x(morphs[i]->get_slot_position(slot_name).get_x());
			pos_end.set_y(morphs[i]->get_slot_position(slot_name).get_y());
		}
	}
	Union morph_union(id_obj, parent_id, slot_name, client_handler);
	for (unsigned int i = 0; i < unions.size(); ++i) {
		if (*(unions[i]) == morph_union) {
			unions[i]->update_path(pos_begin, pos_end);
		}
	}
}