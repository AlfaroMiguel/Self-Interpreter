#include "comunicador_cliente.h"
#include "../common/json.hpp"
#include "recibidor.h"

using json = nlohmann::json;

ComunicadorCliente::ComunicadorCliente(Socket skt_aceptar): //ademas recibe el modelo
	skt_aceptar(std::move(skt_aceptar)), ejecutando(true){}

ComunicadorCliente::~ComunicadorCliente(){
	//delete &skt_aceptar; Ahora es RAII
}

void ComunicadorCliente::atender(){
    Recibidor recibidor(skt_aceptar, *this);
    recibidor.run();
}

void ComunicadorCliente::recibir_mensaje(std::string mensaje){
    json j = json::parse(mensaje);
    std::cerr << j["evento"] << std::endl;

}

bool ComunicadorCliente::esta_ejecutando(){
	return ejecutando;
}

