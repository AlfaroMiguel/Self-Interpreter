#include "comunicador_server.h"
#include <cstdint>
#include <iostream>

ComunicadorServer::ComunicadorServer(std::string& hostname, std::string& puerto){
	skt_cliente.conectar(hostname, puerto);
}

ComunicadorServer::~ComunicadorServer(){}

std::string ComunicadorServer::ejecutar_mensaje(std::string& mensaje){
	char* mensaje_enviar = (char*)mensaje.c_str();
	skt_cliente.enviar(mensaje_enviar, sizeof(char)*8);
	std::cout << "Mensaje enviado: " << mensaje << std::endl;
}
