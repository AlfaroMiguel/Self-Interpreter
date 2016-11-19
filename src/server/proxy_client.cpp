#include "proxy_client.h"
#include "receiver.h"

ProxyClient::ProxyClient(Socket skt_aceptar, VirtualMachine& vm): //ademas recibe el modelo
	socketAccepted(std::move(skt_aceptar)), executing(true), controladorDeEventos(*this), vm(vm){
}

ProxyClient::~ProxyClient(){
	//delete &socketAccepted; Ahora es RAII

}

void ProxyClient::attend(){
    std::cout << "Empiezo a atender" << std::endl;
    Receiver receiver(socketAccepted, *this);
    receiver.run();
    std::cout << "Termino de atender" << std::endl;
    vm.disconnectClient(clientName);
    std::cout << "Desconecto client: " << clientName << std::endl;
}

void ProxyClient::recieveEvent(std::string event){
    controladorDeEventos.handleEvent(event);
}

bool ProxyClient::isExecuting(){
	return executing;
}

void ProxyClient::sendEvent(std::string event){
    std::cout << "Envio evento: " << event << std::endl;
    char* eventToSend = (char*)event.c_str();
    uint32_t tamanio_32 = (uint32_t)htonl(strlen(eventToSend) + 1);
    socketAccepted.enviar((char*)(&tamanio_32), sizeof(tamanio_32));
    socketAccepted.enviar(eventToSend, strlen(eventToSend) + 1);
}