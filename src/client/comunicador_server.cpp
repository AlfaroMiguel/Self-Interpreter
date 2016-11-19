#include "comunicador_server.h"

#include <cstdint>
#include <iostream>

#include "modelo.h"
#include "recibidor.h"
#include "ventana_inicio.h"
#include "cont_eventos.h"
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
		skt_cliente(std::move(otra.skt_cliente)), cont_eventos(otra.cont_eventos){}

void ComunicadorServer::set_control(ControladorEventos* cont_eventos) {
	this->cont_eventos = cont_eventos;
}

ComunicadorServer& ComunicadorServer::operator=(ComunicadorServer&& otra){
	skt_cliente = std::move(otra.skt_cliente);
	cont_eventos = otra.cont_eventos;
	return *this;
}

//que esto se llame enviar codigo
void ComunicadorServer::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	json j;
	j["evento"] = evento.c_str();
	j["codigo"] = mensaje.c_str();
	enviar_json(j);
}

void ComunicadorServer::enviar_datos_morph(const std::string& nombre, const Posicion& pos){
	json j;
	j["evento"] = "crear morph";
	j["id"] = nombre;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	enviar_json(j);
}

void ComunicadorServer::enviar_json(json j){
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
	enviar_json(j);
}

void ComunicadorServer::inicializar() {
	json j;
	j["evento"] = "inicializar";
	enviar_json(j);
}

void ComunicadorServer::enviar_nueva_posicion_morph(const std::string& morph, const Posicion& pos){
	json j;
	j["evento"] = EVENTO_MOVER;
	j["id"] = morph;
	j["x"] = pos.get_x();
	j["y"] = pos.get_y();
	std::cout << "Envio posicion: " << pos.get_x() << ", "<< pos.get_y() << std::endl;
	enviar_json(j);
}

void ComunicadorServer::ingresar_cliente(const std::string& nombre_cliente){
	json j;
	j["evento"] = "conectar cliente";
	j["nombre"] = nombre_cliente;
	enviar_json(j);
	recibidor->start();
}

void ComunicadorServer::recibir_mensaje(const std::string &msj) {
	json j = json::parse((char*)msj.c_str());
	std::string evento = j["evento"];
	std::cout << "evento recibido: " << evento << std::endl;
	EventHandlerSelector event_handler_selector(cont_eventos);
	EventHandler *event_handler =
		event_handler_selector.get_event_handler(evento);
	event_handler->handle(j);
//	std::map<std::string, std::string> dic_slots;
//	if(evento == EVENTO_CREAR) {
//		std::string nombre = j["nombre"];
//		double x = j["posicion"]["x"];
//		double y = j["posicion"]["y"];
//		std::string slots_str = j["slots"];
//		json slots = json::parse((char*)slots_str.c_str());
//		for (json::iterator it = slots.begin(); it != slots.end(); ++it) {
//			std::string nombre = it.key();
//			std::string valor = it.value();
//			dic_slots.insert(std::make_pair(nombre, valor));
//		}
//		Posicion pos_morph(x, y);
//		cont_eventos->crear_morph(nombre, pos_morph, dic_slots);
//	}
//	if (evento == EVENTO_AGREGAR_LOBBIES){
//		std::string lobbies_str = j["lobbies"];
//		json lobbies = json::parse((char*)lobbies_str.c_str());
//		for (json::iterator it = lobbies.begin(); it != lobbies.end(); ++it) {
//			std::string id = it.value();
//			cont_eventos->set_lobby(id);
//		}
//		cont_eventos->iniciar();
//	}
//	if(evento == "cliente conectado"){
//		std::cout << "Se conecta ok" << std::endl;
//		json j;
//		j["evento"] = "inicializar";
//		enviar_json(j);
//		cont_eventos->cliente_conectado();
//	}
//	if(evento == "error"){
//		std::cout << "Ingresa a error" << std::endl;
//		cont_eventos->error_ingreso_cliente();
//	}
//	if (evento == "datos lobby"){
//		//tiene que crear la vm con todos los morphs
//		cont_eventos->crear_vm();
//	}
//	if(evento == EVENTO_MOVER){
//		std::string morph = j["nombre"];
//		double new_x = j["posicion"]["x"];
//		double new_y = j["posicion"]["y"];
//		Posicion new_pos(new_x, new_y);
//		cont_eventos->cambiar_pos_morph(morph, &new_pos);
//	}
}

