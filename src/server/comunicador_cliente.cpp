#include "comunicador_cliente.h"
#include "../common/json.hpp"
#include <cstdint>
#include <string>
#include <vector>

using json = nlohmann::json;

ComunicadorCliente::ComunicadorCliente(Socket skt_aceptar): //ademas recibe el modelo
	skt_aceptar(std::move(skt_aceptar)), ejecutando(true){}

ComunicadorCliente::~ComunicadorCliente(){
	//delete &skt_aceptar; Ahora es RAII
}

void ComunicadorCliente::recibir_mensaje(){
	char* tamanio_mensaje = (char*) malloc(4);
	skt_aceptar.recibir(tamanio_mensaje, 4);
    uint32_t tamanio = (ntohl(*(uint32_t*)tamanio_mensaje));

	std::cout << "Tamanio mensaje: " << tamanio << std::endl;
    char* buffer_evento = (char*)malloc(tamanio);

    skt_aceptar.recibir(buffer_evento, tamanio);
    std::cout << "Mensaje recibido: " << buffer_evento<< std::endl;

    json j = json::parse(buffer_evento);

    std::string evento = j["evento"];

    std::cout << "El evento es: " << evento << std::endl;
}

bool ComunicadorCliente::esta_ejecutando(){
	return ejecutando;
}

