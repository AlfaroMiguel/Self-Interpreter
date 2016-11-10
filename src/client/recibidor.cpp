#include "recibidor.h"

Recibidor::Recibidor(Socket& skt, ComunicadorServer& com_server): skt(skt), com_server(com_server){
	esta_recibiendo = true;
}

Recibidor::~Recibidor(){}

void Recibidor::recibir(){
	char* tam_buffer = (char*) malloc(sizeof(uint32_t));
	std::cout << "afuera" << std::endl;
	while(skt.recibir(tam_buffer, sizeof(uint32_t))){
		std::cout << "adentro" << std::endl;
		uint32_t tam = (ntohl)(*(uint32_t*)tam_buffer);
		char* msj_buffer = (char*) malloc(sizeof(char)*tam);
		skt.recibir(msj_buffer, tam);
		std::string msj(msj_buffer);
		com_server.recibir_mensaje(msj);
		free(msj_buffer);
	}
	free(tam_buffer);
}

