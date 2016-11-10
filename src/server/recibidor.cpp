#include "recibidor.h"

Recibidor::Recibidor(Socket& skt, ComunicadorCliente& com_cliente): skt(skt), com_cliente(com_cliente){
	esta_recibiendo = true;
}

Recibidor::~Recibidor(){}

void Recibidor::recibir(){
	char* tam_buffer = (char*) malloc(sizeof(uint32_t));
	std::cout << "Voy a recibir" << std::endl;
	while(skt.recibir(tam_buffer, sizeof(uint32_t))){
		uint32_t tam = (ntohl)(*(uint32_t*)tam_buffer);
		char* msj_buffer = (char*) malloc(sizeof(char)*tam);
		skt.recibir(msj_buffer, tam);
		std::string evnt(msj_buffer);
		std::cout << "Recibi: " << evnt << std::endl;
 		com_cliente.recibirEvento(evnt);
		free(msj_buffer);
	}
	free(tam_buffer);
}
