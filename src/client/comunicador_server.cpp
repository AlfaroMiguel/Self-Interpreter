#include "comunicador_server.h"
#include <cstdint>
#include <iostream>
#include "../common/json.hpp"
#include "../../../../../../usr/include/c++/6/cstdint"

using json = nlohmann::json;

ComunicadorServer::ComunicadorServer(std::string& hostname, std::string& puerto){
	skt_cliente.conectar(hostname, puerto);
}

ComunicadorServer::ComunicadorServer() {}
ComunicadorServer::~ComunicadorServer(){}

ComunicadorServer::ComunicadorServer(ComunicadorServer &&otra): skt_cliente(std::move(otra.skt_cliente)){}

ComunicadorServer& ComunicadorServer::operator=(ComunicadorServer&& otra){
	skt_cliente = std::move(otra.skt_cliente);
	return *this;
}
void ComunicadorServer::ejecutar_mensaje(const std::string& mensaje){

	json j;
	j["evento"] = "codigo";
	j["codigo"] = "( | x <- 5. | ).";
	std::string s = j.dump();

    std::cout<< s.size() << std::endl;

	char* evento_enviar = (char*)s.c_str();

    size_t tamanio_t = strlen(evento_enviar);

    uint32_t tamanio_32 = (uint32_t)htonl(strlen(evento_enviar));
	skt_cliente.enviar((char*)(&tamanio_32), sizeof(tamanio_32));

    skt_cliente.enviar(evento_enviar, tamanio_t);

	std::cout << "Mensaje enviado: " << evento_enviar << std::endl;
}
