#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "../common/socket.h"
#include "../common/json.hpp"
#include <string>
#include "posicion.h"

using json = nlohmann::json;
class Recibidor;
class Modelo;
class ClientHandler;

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
  //TODO: siempre llamar a enviar mensaje con el hash que le devuelva a que funcion llamar segun el evento,
  //TODO: idem para recibir mensaje
 	private:
  		Socket skt_cliente;
  		ClientHandler* client_handler;
		Recibidor* recibidor;

  		ComunicadorServer(const ComunicadorServer& otra) = delete;
  		ComunicadorServer& operator=(const ComunicadorServer& otra) = delete;

  		void send_json(json j);
 	public:
  		ComunicadorServer(const std::string& hostname, const std::string& puerto);
  		ComunicadorServer();
  		~ComunicadorServer();

  		ComunicadorServer(ComunicadorServer&& otra);
  		ComunicadorServer& operator=(ComunicadorServer&& otra);

  		void inicializar();
  		void set_control(ClientHandler* client_handler);
  		void recibir_mensaje(const std::string& msj);
  		void enviar_datos_cliente(const std::string& lobby, const std::string& nombre_cliente);
  		void enviar_datos_morph(const std::string& mensaje, const Posicion& pos);
  		void enviar_mensaje(const std::string& consulta, const std::string& evento);
  		void enviar_nueva_posicion_morph(int morph_id, const Posicion& pos);
  		void ingresar_cliente(const std::string& nombre_cliente);
  		void get_morph_from_slot(int morph_id, const std::string& slot_name);
};
#endif