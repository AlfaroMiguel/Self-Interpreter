#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "../common/socket.h"
#include "../common/json.hpp"
#include <string>


using json = nlohmann::json;
class Recibidor;
class Modelo;
/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
 	private:
  		Socket skt_cliente;
  		Modelo* modelo;
		Recibidor* recibidor;
  		ComunicadorServer(const ComunicadorServer& otra) = delete;
  		ComunicadorServer& operator=(const ComunicadorServer& otra) = delete;

  		void enviar_json(json j);
 	public:
  		ComunicadorServer(const std::string& hostname, const std::string& puerto);
  		ComunicadorServer();
  		~ComunicadorServer();

  		ComunicadorServer(ComunicadorServer&& otra);
  		ComunicadorServer& operator=(ComunicadorServer&& otra);

  		void inicializar();
  		void set_modelo(Modelo* modelo);
  		void recibir_mensaje(std::string& msj);
  		void enviar_datos_cliente(const std::string& lobby, const std::string& nombre_cliente);
  		void enviar_mensaje(const std::string& consulta, const std::string& evento);

};
#endif