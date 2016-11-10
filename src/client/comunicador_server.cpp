#include "comunicador_server.h"
#include <cstdint>
#include <iostream>
#include "modelo.h"

#define EVENTO_MODIFICAR "modificar"
#define EVENTO_CREAR "crear"

using json = nlohmann::json;

ComunicadorServer::ComunicadorServer(const std::string& hostname, const std::string& puerto){
	skt_cliente.conectar(hostname, puerto);
}

ComunicadorServer::~ComunicadorServer(){}

ComunicadorServer::ComunicadorServer(ComunicadorServer &&otra):
		skt_cliente(std::move(otra.skt_cliente)), modelo(otra.modelo){}

void ComunicadorServer::set_modelo(Modelo* modelo) {
	this->modelo = modelo;
}
ComunicadorServer& ComunicadorServer::operator=(ComunicadorServer&& otra){
	skt_cliente = std::move(otra.skt_cliente);
	modelo = otra.modelo;
	return *this;
}

void ComunicadorServer::inicializar(){
	json j;
	j["evento"] = "inicializar";
	enviar_json(j);
}

void ComunicadorServer::enviar_mensaje(const std::string& mensaje, const std::string& evento){
	json j;
	j["evento"] = evento.c_str();
	j["codigo"] = mensaje.c_str();
	enviar_json(j);
}

void ComunicadorServer::enviar_json(json j){
	std::string s = j.dump();

	char* evento_enviar = (char*)s.c_str();

	uint32_t tamanio_32 = (uint32_t)htonl(strlen(evento_enviar));
	skt_cliente.enviar((char*)(&tamanio_32), sizeof(tamanio_32));

	skt_cliente.enviar(evento_enviar, strlen(evento_enviar));
}

void ComunicadorServer::enviar_datos_cliente(const std::string& lobby, const std::string& nombre_cliente){
	json j;
	j["evento"] = "datos cliente";
	j["lobby"] = std::stoi(lobby);
	j["nombre"] = nombre_cliente.c_str();
	enviar_json(j);
}

void ComunicadorServer::recibir_mensaje(std::string &msj) {
	json j = json::parse((char*)msj.c_str());
	std::string evento = j["evento"];
	std::map<std::string, std::string> dic_slots;
	if(evento == EVENTO_CREAR) {
		std::string nombre = j["nombre"];
		double x = j["posicion"]["x"];
		double y = j["posicion"]["y"];
		/*json slots = j["slots"];
		for (json::iterator it = slots.begin(); it != slots.end(); ++it)
			dic_slots.insert(std::make_pair(it.key(), it.value()));*/
		modelo->crear_morph(nombre, x, y, dic_slots);
	}
	if (evento == "agregar lobby"){
		std::string id = j["id"];
		modelo->set_lobby(id);
	}
	if(evento == "iniciar"){
		modelo->iniciar();
	}
	if(evento == "cliente conectado"){
		//tiene que crear la vm con todos los morphs
		modelo->crear_vm();
	}
	if(evento == "error cliente"){
		//mandar al modelo que levante una ventana de error
	}
}

