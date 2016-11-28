#include "client_handler.h"

#include "modelo.h"
#include "server_proxy.h"
#include "ventana_inicio.h"
#include "view_handler.h"

#include <iostream>

ClientHandler::ClientHandler(Modelo* modelo,
							 ServerProxy* server_proxy):
	modelo(modelo),
	server_proxy(server_proxy) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::set_handler(ViewHandler* view_handler) {
	this->view_handler = view_handler;
}

void ClientHandler::add_lobby(const std::string& lobby_id) const{
	view_handler->add_lobby(lobby_id);
}

void ClientHandler::set_lobbies() const{
	view_handler->set_lobbies();
}

void ClientHandler::open_lobby(){
	view_handler->open_lobby();
}

void ClientHandler::move_morph(int morph_id, const Posicion& new_pos){
	modelo->move_morph(morph_id, new_pos);
}

void ClientHandler::update_morph_position(int morph_id, const Posicion& pos){
	server_proxy->send_morph_position(morph_id, pos);
}

void ClientHandler::enable_editing(Glib::RefPtr<Morph> morph){
	view_handler->enable_editing(morph);
}

void ClientHandler::create_morph(const std::string& name,
								 const Posicion& pos,
								 std::map<std::string, std::string> slots,
								 int id, int id_padre,
								 const std::string& slot_name){
	modelo->create_morph(name, pos, slots, id, id_padre, slot_name);
}

void ClientHandler::draw_morph(Glib::RefPtr<Morph> morph){
	view_handler->draw_morph(morph);
}

void ClientHandler::dismiss_morph() {
	modelo->dismiss_morph();
}

void ClientHandler::dismiss_morph(int id) {
	modelo->dismiss_morph(id);
}

void ClientHandler::hide_morph(Glib::RefPtr<Morph> morph){
	view_handler->dismiss_morph(morph);
}

void ClientHandler::dismiss_morph(Glib::RefPtr<Morph> morph) {
	hide_morph(morph);
	server_proxy->dismiss_morph(morph->get_id());
}

bool ClientHandler::button_event(GdkEventButton *event) {
	if((event->type == GDK_2BUTTON_PRESS) && (event->button == 1)) {
		Posicion event_pos(event->x, event->y);
		if (modelo->es_objeto(event_pos)) {
			modelo->seleccionar_morph(event_pos);
			modelo->editar_morph();
		}
		if (modelo->es_slot(event_pos))
			modelo->get_morph_from_slot(event_pos);
		return true;
	}
	return false;
}

void ClientHandler::change_morph_name(const std::string& new_name){
	modelo->cambiar_nombre_morph(new_name);
	server_proxy->change_morph_name(new_name,
								  modelo->get_selected_morph()->get_id());
}

void ClientHandler::send_code(const std::string& code,
							  const std::string& event){
	if (code.empty()) return;
	server_proxy->send_code(code, event, modelo->get_selected_morph()->get_id());
}

void ClientHandler::connect_client(const std::string &client_name) {
	server_proxy->connect_client(client_name);
}

void ClientHandler::change_morph_position(int morph_id,
										  const Posicion& new_pos){
	modelo->change_morph_position(morph_id, new_pos);
}

void ClientHandler::client_connection_error() {
	view_handler->client_connection_error();
}

void ClientHandler::connected_client(){
	server_proxy->inicializar();
	view_handler->ocultar_vista_cliente();
}

void ClientHandler::get_morph_from_slot(int morph_id,
										const std::string& slot_name) {
	server_proxy->get_morph_from_slot(morph_id, slot_name);
}

void ClientHandler::select_lobby(const std::string& lobby_name,
								 const std::string& lobby_property){
	server_proxy->send_selected_lobby(lobby_name, lobby_property);
}

void ClientHandler::quit(){
	view_handler->quit();
}

void ClientHandler::show_lobby_options(){
	view_handler->show_lobby_options();
}

void ClientHandler::reset_lobby(){
	modelo->reset_lobby();
}

void ClientHandler::join_morphs(const Posicion& pos_begin, const Posicion& pos_end){
	//view_handler->join_morphs(const Posicion& pos_begin, const Posicion& pos_end);
}

void ClientHandler::add_union(Union* morph_union) {
	view_handler->add_union(morph_union);
}

void ClientHandler::add_union(int id_obj, int id_padre, const std::string& slot_name){
	modelo->add_union(id_obj, id_padre, slot_name);
}

void ClientHandler::delete_union(Union* morph_union){
	//modelo->delete_union(morph_union);
	view_handler->delete_union(morph_union);
}