#include "proxy_client.h"
#include "receiver.h"
#include "event_handler_selector.h"
#include "server_handler.h"
#include "event_handler.h"

using json = nlohmann::json;

ProxyClient::ProxyClient(Socket skt_aceptar, VirtualMachine& vm): //ademas recibe el modelo
	socketAccepted(std::move(skt_aceptar)), executing(true), vm(vm), eventHandlerSelector(new ServerHandler(*this)){
}

ProxyClient::~ProxyClient(){
	//delete &socketAccepted; Ahora es RAII

}

void ProxyClient::attend(){
    std::cout << "Empiezo a atender" << std::endl;
    Receiver receiver(socketAccepted, *this);
    receiver.run();
    std::cout << "Termino de atender" << std::endl;
    if(!validClient)return;
    vm.disconnectClient(clientName);
    std::cout << "Desconecto client: " << clientName << std::endl;
}

void ProxyClient::recieveEvent(std::string event){
    json eventJ = json::parse(event);
    EventHandler* eventHandler = eventHandlerSelector.get_event_handler(eventJ["evento"]);
    if(eventHandler != nullptr)
        eventHandler->handle(eventJ);
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