#include "aceptador.h"
#include "socket_error.h"
#include <iostream>
#define CLIENTE_CONECTADO  "Cliente conectado."

Aceptador::Aceptador(Socket& skt_server, std::string& puerto):
	skt_server(skt_server), aceptando(true){
	skt_server.bind_and_listen(puerto);
}

Aceptador::~Aceptador(){}

void Aceptador::aceptar(){
	while(aceptando) {
		Socket *socket = new Socket();
		try {
			skt_server.aceptar(*socket);
		}
		catch(const SocketError& error){
			delete socket;
			aceptando = false;
			continue;
		}
		ComunicadorCliente *comunicadorCliente =
			new ComunicadorCliente(*socket);
		std::cerr << CLIENTE_CONECTADO << std::endl;
		comunicadorCliente->start();
		limpiar_clientes();
		clientes.push_back(comunicadorCliente);
	}
	terminar();
}

void Aceptador::terminar() {
	for(Thread* cliente: clientes) {
		cliente->join();
		delete cliente;
	}
}

void Aceptador::limpiar_clientes(){
	int i = 0;
	for(ComunicadorCliente* cliente: clientes) {
		if (cliente->esta_ejecutando()) {
			cliente->join();
			delete cliente;
			clientes.erase(clientes.begin()+i);
			i++;
		}
	}
}

