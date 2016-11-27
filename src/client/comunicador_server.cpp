#include "comunicador_server.h"

#include <cstdint>
#include <iostream>

#include "modelo.h"
#include "recibidor.h"
#include "ventana_inicio.h"
#include "client_handler.h"
#include "event_handler.h"
#include "event_handler_selector.h"
#define EVENTO_MODIFICAR "modificar"
#define EVENTO_CREAR "crear"
#define EVENTO_AGREGAR_LOBBIES "agregar lobbies"
#define EVENTO_MOVER "mover morph"
#define JSON_ID_EVENT "evento"
#define JSON_ID_CODE "codigo"

using json = nlohmann::json;

ComunicadorServer::ComunicadorServer(const std::string &hostname, const std::string &puerto) {
	skt_cliente.conectar(hostname, puerto);
	recibidor = new Recibidor(skt_cliente, *this);
}

ComunicadorServer::~ComunicadorServer() {
	skt_cliente.shutdown();
	if (recibidor->is_active())
		recibidor->join();
	delete recibidor;
}

ComunicadorServer::ComunicadorServer(ComunicadorServer &&otra) :
	skt_cliente(std::move(otra.skt_cliente)), client_handler(otra.client_handler) {}

void ComunicadorServer::set_control(ClientHandler *client_handler) {
	this->client_handler = client_handler;
}

ComunicadorServer &ComunicadorServer::operator=(ComunicadorServer &&otra) {
	skt_cliente = std::move(otra.skt_cliente);
	client_handler = otra.client_handler;
	return *this;
}

void ComunicadorServer::send_code(const std::string &code, const std::string &event, int morph_id) {
	json j;
	j[JSON_ID_EVENT] = event.c_str();
	j[JSON_ID_CODE] = code.c_str();
	j["morph id"] = morph_id;
	send_json(j);
}

void ComunicadorServer::enviar_datos_morph(const std::string &nombre, const Posicion &pos) {
	json j;
	j[JSON_ID_EVENT] = "crear morph";
	j["id"] = nombre;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	send_json(j);
}

void ComunicadorServer::get_morph_from_slot(int morph_id, const std::string &slot_name) {
	json j;
	j[JSON_ID_EVENT] = "get morph";
	j["morph id"] = morph_id;
	j["slot name"] = slot_name;
	send_json(j);
}

void ComunicadorServer::send_json(const json &j) {
	std::string s = j.dump();
	char *evento_enviar = (char *) s.c_str();
	uint32_t tamanio_32 = htonl((uint32_t)(strlen(evento_enviar) + 1));
	skt_cliente.enviar((char *) (&tamanio_32), sizeof(uint32_t));
	std::cout << "Envio evento: " << evento_enviar << std::endl;
	skt_cliente.enviar(evento_enviar, strlen(evento_enviar) + 1);
}

void ComunicadorServer::send_selected_lobby(const std::string &lobby_name,
											const std::string &lobby_property) {
	json j;
	j[JSON_ID_EVENT] = "elegir lobby";
	j["lobby"] = lobby_name;
	j["estado"] = lobby_property;
	send_json(j);
}

void ComunicadorServer::inicializar() {
	json j;
	j[JSON_ID_EVENT] = "inicializar";
	send_json(j);
}

void ComunicadorServer::send_morph_position(int morph_id, const Posicion &pos) {
	json j;
	j[JSON_ID_EVENT] = EVENTO_MOVER;
	j["id"] = morph_id;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	send_json(j);
}

void ComunicadorServer::connect_client(const std::string &client_name) {
	json j;
	j[JSON_ID_EVENT] = "conectar cliente";
	j["nombre"] = client_name;
	send_json(j);
	recibidor->start();
}

void ComunicadorServer::change_morph_name(const std::string &new_name, int morph_id) {
	json j;
	j[JSON_ID_EVENT] = "change name";
	j["id"] = morph_id;
	j["new name"] = new_name;
	send_json(j);
}

void ComunicadorServer::dismiss_morph(int morph_id) {
	json j;
	j[JSON_ID_EVENT] = "dismiss";
	j["id"] = morph_id;
	send_json(j);
}

void ComunicadorServer::recibir_mensaje(const std::string &msj) {
	json j = json::parse((char *) msj.c_str());
	std::string evento = j[JSON_ID_EVENT];
	std::cout << "evento recibido: " << evento << std::endl;
	EventHandlerSelector event_handler_selector(client_handler);
	EventHandler *event_handler =
		event_handler_selector.get_event_handler(evento);
	event_handler->handle(j);
	std::map<std::string, std::string> dic_slots;
}

