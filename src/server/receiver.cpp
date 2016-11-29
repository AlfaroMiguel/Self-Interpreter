#include "receiver.h"

Receiver::Receiver(Socket& skt, ProxyClient& client): skt(skt), client(client){
	isReceiving = true;
}

Receiver::~Receiver(){}

void Receiver::receive(){
	char* tam_buffer = (char*) malloc(sizeof(uint32_t));
	while(skt.recibir(tam_buffer, sizeof(uint32_t))){
		uint32_t tam = (ntohl)(*(uint32_t*)tam_buffer);
		char* msj_buffer = (char*) malloc(sizeof(char)*tam);
		skt.recibir(msj_buffer, tam);
		std::string evnt(msj_buffer);
        client.recieveEvent(evnt);
		free(msj_buffer);
	}
	free(tam_buffer);
}
