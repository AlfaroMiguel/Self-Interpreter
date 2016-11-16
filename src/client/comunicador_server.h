#ifndef COMUNICADOR_SERVER_H
#define COMUNICADOR_SERVER_H

#include "../common/socket.h"
#include "../common/json.hpp"
#include <string>


using json = nlohmann::json;
class Recibidor;
class Modelo;
class ControladorEventos;

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del servidor. */
class ComunicadorServer {
  //TODO: siempre llamar a enviar mensaje con el hash que le devuelva a que funcion llamar segun el evento,
  //TODO: idem para recibir mensaje
 	private:
  		Socket skt_cliente;
  		ControladorEventos* cont_eventos;
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
  		void set_control(ControladorEventos* cont_eventos);
  		void recibir_mensaje(const std::string& msj);
  		void enviar_datos_cliente(const std::string& lobby, const std::string& nombre_cliente);
  		void enviar_datos_morph(const std::string& mensaje, double x, double y);
  		void enviar_mensaje(const std::string& consulta, const std::string& evento);
  		void enviar_nueva_posicion_morph(const std::string& morph, double x, double y);
  		void ingresar_cliente(const std::string& nombre_cliente);
};
#endif