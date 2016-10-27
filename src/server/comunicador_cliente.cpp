#include "comunicador_cliente.h"

#include <cstdint>
#include <string>
#include <vector>

ComunicadorCliente::ComunicadorCliente(Socket& skt_aceptar): //ademas recibe el modelo
	skt_aceptar(skt_aceptar), ejecutando(true){}

ComunicadorCliente::~ComunicadorCliente(){
	//delete &skt_aceptar;
}

void ComunicadorCliente::recibir_mensaje(){
	char* buffer_mensaje = (char*) malloc(sizeof(char)*100);
	skt_aceptar.recibir(buffer_mensaje, sizeof(char)*100);
	std::string mensaje(buffer_mensaje);
	std::cout << "Mensaje recibido: " << mensaje << std::endl;
}

bool ComunicadorCliente::esta_ejecutando(){
	return ejecutando;
}

