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
 	private:
  		Socket skt_cliente;
  		ClientHandler* client_handler;
		Recibidor* recibidor;

  		ComunicadorServer(const ComunicadorServer& otra) = delete;
  		ComunicadorServer& operator=(const ComunicadorServer& otra) = delete;

  		void send_json(const json& j);
 	public:
  		ComunicadorServer(const std::string& hostname, const std::string& puerto);
  		ComunicadorServer();
  		~ComunicadorServer();

  		ComunicadorServer(ComunicadorServer&& otra);
  		ComunicadorServer& operator=(ComunicadorServer&& otra);

  		void inicializar();
  		void set_control(ClientHandler* client_handler);
  		void recibir_mensaje(const std::string& msj);
  		void send_selected_lobby(const std::string& lobby, const std::string& lobby_property);
  		void enviar_datos_morph(const std::string& mensaje, const Posicion& pos);
  		void send_code(const std::string& consulta, const std::string& evento, int morph_id);
  		/* Envia al servidor la posicion actual del morph */
  		void send_morph_position(int morph_id, const Posicion& pos);
  		/* Informa al servidor el nombre del cliente que se intenta conectar */
  		void connect_client(const std::string& client_name);
  		void get_morph_from_slot(int morph_id, const std::string& slot_name);
  		void change_morph_name(const std::string& new_name, int morph_id);
  		void dismiss_morph(int morph_id);
};
#endif
