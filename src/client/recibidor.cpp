#include "recibidor.h"

Recibidor::Recibidor(Socket& skt, ComunicadorServer& com_server): skt(skt), com_server(com_server){
	esta_recibiendo = false;
}

Recibidor::~Recibidor(){}

void Recibidor::recibir(){
	if (! esta_recibiendo) {
		std::cout << "Empiezo a recibir" << std::endl;
		esta_recibiendo = true;
		char *tam_buffer = (char *) malloc(sizeof(uint32_t));
		while (skt.recibir(tam_buffer, sizeof(uint32_t))) {
			uint32_t tam = (ntohl)(*(uint32_t *) tam_buffer);
			char *msj_buffer = (char *) malloc(sizeof(char) * tam);
			skt.recibir(msj_buffer, tam);
			std::string msj(msj_buffer);
			std::cout << "Mensaje recibido: " << msj << std::endl;
			com_server.recibir_mensaje(msj);
			free(msj_buffer);
		}
		free(tam_buffer);
	}
}

