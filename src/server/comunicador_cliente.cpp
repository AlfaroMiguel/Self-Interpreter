#include "comunicador_cliente.h"
#include "recibidor.h"

ComunicadorCliente::ComunicadorCliente(Socket skt_aceptar, VirtualMachine& vm): //ademas recibe el modelo
	skt_aceptar(std::move(skt_aceptar)), ejecutando(true), controladorDeEventos(*this), vm(vm){
}

ComunicadorCliente::~ComunicadorCliente(){
	//delete &skt_aceptar; Ahora es RAII

}

void ComunicadorCliente::atender(){
    std::cout << "Empiezo a atender" << std::endl;
    Recibidor recibidor(skt_aceptar, *this);
    recibidor.run();
    std::cout << "Termino de atender" << std::endl;
    vm.disconnectClient(clientName);
    std::cout << "Desconecto cliente: " << clientName << std::endl;
}

void ComunicadorCliente::recibirEvento(std::string evento){
    controladorDeEventos.resolverEvento(evento);
}

bool ComunicadorCliente::esta_ejecutando(){
	return ejecutando;
}

void ComunicadorCliente::enviarEvento(std::string evento){
    std::cout << "Envio evento: " << evento << std::endl;
    char* evento_enviar = (char*)evento.c_str();
    uint32_t tamanio_32 = (uint32_t)htonl(strlen(evento_enviar) + 1);
    skt_aceptar.enviar((char*)(&tamanio_32), sizeof(tamanio_32));
    skt_aceptar.enviar(evento_enviar, strlen(evento_enviar) + 1);
}