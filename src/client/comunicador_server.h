#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "socket.h"
#include <string>

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
 	private:
  		Socket skt_cliente;
  		ComunicadorServer(const ComunicadorServer& otra) = delete;
  		ComunicadorServer& operator=(const ComunicadorServer& otra) = delete;

 	public:
  		ComunicadorServer(std::string& hostname, std::string& puerto);
  		ComunicadorServer();
  		~ComunicadorServer();

  		ComunicadorServer(ComunicadorServer&& otra);
  		ComunicadorServer& operator=(ComunicadorServer&& otra);

  		std::string ejecutar_mensaje(const std::string& consulta);
};
#endif