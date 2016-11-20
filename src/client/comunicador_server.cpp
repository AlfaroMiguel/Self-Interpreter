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

using json = nlohmann::json;

ComunicadorServer::ComunicadorServer(const std::string& hostname, const std::string& puerto){
	skt_cliente.conectar(hostname, puerto);
    recibidor = new Recibidor(skt_cliente, *this);

}

ComunicadorServer::~ComunicadorServer(){
	skt_cliente.shutdown();
	recibidor->join();
    delete recibidor;
}

ComunicadorServer::ComunicadorServer(ComunicadorServer &&otra):
		skt_cliente(std::move(otra.skt_cliente)), client_handler(otra.client_handler){}

void ComunicadorServer::set_control(ClientHandler* client_handler) {
	this->client_handler = client_handler;
}

ComunicadorServer& ComunicadorServer::operator=(ComunicadorServer&& otra){
	skt_cliente = std::move(otra.skt_cliente);
	client_handler = otra.client_handler;
	return *this;
}

//que esto se llame enviar codigo
void ComunicadorServer::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	json j;
	j["evento"] = evento.c_str();
	j["codigo"] = mensaje.c_str();
	send_json(j);
}

void ComunicadorServer::enviar_datos_morph(const std::string& nombre, const Posicion& pos){
	json j;
	j["evento"] = "crear morph";
	j["id"] = nombre;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	send_json(j);
}

void ComunicadorServer::get_morph_from_slot(int morph_id, const std::string& slot_name) {
	json j;
	j["evento"] = "get morph";
	j["morph id"] = morph_id;
	j["slot name"] = slot_name;
	send_json(j);
}

void ComunicadorServer::send_json(json j){
	std::string s = j.dump();

	char* evento_enviar = (char*)s.c_str();

	uint32_t tamanio_32 = htonl((uint32_t)(strlen(evento_enviar) + 1));

	std::cout << tamanio_32 << std::endl;
	skt_cliente.enviar((char*)(&tamanio_32), sizeof(uint32_t));

	std::cout << "Envio evento: " << evento_enviar << std::endl;
	skt_cliente.enviar(evento_enviar, strlen(evento_enviar) + 1);
}

void ComunicadorServer::enviar_datos_cliente(const std::string& lobby, const std::string& estado_lobby){
	json j;
	j["evento"] = "elegir lobby";
	j["lobby"] = lobby;
	j["estado"] = estado_lobby;
	send_json(j);
}

void ComunicadorServer::inicializar() {
	json j;
	j["evento"] = "inicializar";
	send_json(j);
}

void ComunicadorServer::send_morph_position(int morph_id, const Posicion& pos){
	json j;
	j["evento"] = EVENTO_MOVER;
	j["id"] = morph_id;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	send_json(j);
}

void ComunicadorServer::ingresar_cliente(const std::string& nombre_cliente){
	json j;
	j["evento"] = "conectar cliente";
	j["nombre"] = nombre_cliente;
	send_json(j);
	recibidor->start();
}

void ComunicadorServer::recibir_mensaje(const std::string &msj) {
	json j = json::parse((char*)msj.c_str());
	std::string evento = j["evento"];
	std::cout << "evento recibido: " << evento << std::endl;
	EventHandlerSelector event_handler_selector(client_handler);
	EventHandler *event_handler =
		event_handler_selector.get_event_handler(evento);
	event_handler->handle(j);
	std::map<std::string, std::string> dic_slots;
}

