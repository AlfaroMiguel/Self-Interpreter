#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "../common/socket.h"
#include <string>

class Modelo;
/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
 	private:
  		Socket skt_cliente;
  		Modelo* modelo;

  		ComunicadorServer(const ComunicadorServer& otra) = delete;
  		ComunicadorServer& operator=(const ComunicadorServer& otra) = delete;

 	public:
  		ComunicadorServer(const std::string& hostname, const std::string& puerto);
  		ComunicadorServer();
  		~ComunicadorServer();

  		ComunicadorServer(ComunicadorServer&& otra);
  		ComunicadorServer& operator=(ComunicadorServer&& otra);

  		void set_modelo(Modelo* modelo);
  		void enviar_mensaje(const std::string& consulta, const std::string& evento);
  		void recibir_mensaje(std::string& msj);
};
#endif