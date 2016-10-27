#include "comunicador_server.h"
#include <cstdint>
#include <iostream>

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
	char* mensaje_enviar = (char*)mensaje.c_str();
	skt_cliente.enviar(mensaje_enviar, sizeof(char)*100);
	std::cout << "Mensaje enviado: " << mensaje << std::endl;
}
