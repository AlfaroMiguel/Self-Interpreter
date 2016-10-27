#include "aceptador.h"
#include "../common/socket.h"
#include <iostream>
#define CLIENTE_CONECTADO  "Cliente conectado."

//Template del remove_if si hacia el include<algorithm> rompia el SERCOM
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first,
						  ForwardIterator last,
						  UnaryPredicate pred)
{
	ForwardIterator result = first;
	while (first!=last) {
		if (!pred(*first)) {
			*result = std::move(*first);
			++result;
		}
		++first;
	}
	return result;
}

bool hay_que_eliminar_cliente(ComunicadorCliente* cliente){
	return cliente == NULL;
}

Aceptador::Aceptador(Socket& skt_server, std::string& puerto):
	skt_server(skt_server), aceptando(true){
	skt_server.bind_and_listen(puerto);
}

Aceptador::~Aceptador(){}

void Aceptador::aceptar(){
	while(aceptando) {
		Socket socket;
		try {skt_server.aceptar(socket);}
		catch(const SocketError& error){
			aceptando = false;
			continue;
		}
		ComunicadorCliente *comunicadorCliente = new ComunicadorCliente(socket);
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
	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i]->esta_ejecutando()) {
			clientes[i]->join();
			delete clientes[i];
			clientes[i] = NULL;
		}
	}
	clientes.erase(remove_if(clientes.begin(),
							 clientes.end(),
							 hay_que_eliminar_cliente),
				   clientes.end());
}

