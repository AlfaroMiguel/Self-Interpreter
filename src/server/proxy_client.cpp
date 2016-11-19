#include "comunicador_cliente.h"
#include "recibidor.h"

ProxyClient::ProxyClient(Socket skt_aceptar, VirtualMachine& vm): //ademas recibe el modelo
	socketAccepted(std::move(skt_aceptar)), executing(true), controladorDeEventos(*this), vm(vm){
}

ProxyClient::~ProxyClient(){
	//delete &socketAccepted; Ahora es RAII

}

void ProxyClient::atender(){
    std::cout << "Empiezo a atender" << std::endl;
    Recibidor recibidor(socketAccepted, *this);
    recibidor.run();
    std::cout << "Termino de atender" << std::endl;
    vm.disconnectClient(clientName);
    std::cout << "Desconecto cliente: " << clientName << std::endl;
}

void ProxyClient::recibirEvento(std::string evento){
    controladorDeEventos.resolverEvento(evento);
}

bool ProxyClient::isExecuting(){
	return executing;
}

void ProxyClient::enviarEvento(std::string evento){
    std::cout << "Envio evento: " << evento << std::endl;
    char* evento_enviar = (char*)evento.c_str();
    uint32_t tamanio_32 = (uint32_t)htonl(strlen(evento_enviar) + 1);
    socketAccepted.enviar((char*)(&tamanio_32), sizeof(tamanio_32));
    socketAccepted.enviar(evento_enviar, strlen(evento_enviar) + 1);
}