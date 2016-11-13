#include "comunicador_server.h"

#include <cstdint>
#include <iostream>

#include "modelo.h"
#include "recibidor.h"
#include "ventana_inicio.h"
#include "cont_eventos.h"

#define EVENTO_MODIFICAR "modificar"
#define EVENTO_CREAR "crear"

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

void ComunicadorServer::inicializar(){
	json j;
	j["evento"] = "inicializar";
	enviar_json(j);
    recibidor->start();
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

	uint32_t tamanio_32 = htonl((uint32_t)(strlen(evento_enviar) + 1));

	std::cout << tamanio_32 << std::endl;
	skt_cliente.enviar((char*)(&tamanio_32), sizeof(uint32_t));

	std::cout << evento_enviar << std::endl;
	skt_cliente.enviar(evento_enviar, strlen(evento_enviar) + 1);
}

void ComunicadorServer::enviar_datos_cliente(const std::string& lobby, const std::string& nombre_cliente){
	json j;
	j["evento"] = "conectar";
	j["lobby"] = lobby;
	j["nombre"] = nombre_cliente;
	enviar_json(j);
}

void ComunicadorServer::enviar_nueva_posicion_morph(const std::string& morph, double x, double y){
	json j;
	j["evento"] = "mover morph";
	j["id"] = morph;
	j["x"] = x;
	j["y"] = y;
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
		cont_eventos->crear_morph(nombre, x, y, dic_slots);
	}

	if (evento == "agregar lobby"){
		std::string id = j["id"];
		cont_eventos->set_lobby(id);
	}
	if(evento == "iniciar"){
		cont_eventos->iniciar();
	}
	if(evento == "cliente conectado"){
		//tiene que crear la vm con todos los morphs
		cont_eventos->crear_vm();
	}
	if(evento == "error cliente"){
		//mandar al modelo que levante una ventana de error
	}
	if(evento == "mover morph"){
		std::string morph = j["id"];
		double new_x = j["x"];
		double new_y = j["y"];
		cont_eventos->mover_morph(morph, new_x, new_y);
	}
}
