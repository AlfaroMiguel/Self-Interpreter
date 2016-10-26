#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "socket.h"
#include <string>

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
 	private:
  		Socket skt_cliente;
 	public:
  		ComunicadorServer(std::string& hostname, std::string& puerto);
  		~ComunicadorServer();
  		std::string ejecutar_mensaje(std::string& consulta);
};
#endif