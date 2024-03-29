#include "proxy_client.h"
#include "receiver.h"
#include "handlers/event_handler_selector.h"
#include "handlers/server_handler.h"
#include "handlers/event_handler.h"

using json = nlohmann::json;

ProxyClient::ProxyClient(Socket skt_aceptar, VirtualMachine& vm): //ademas recibe el modelo
	socketAccepted(std::move(skt_aceptar)), executing(true), vm(vm), eventHandlerSelector(new ServerHandler(*this)){
}

ProxyClient::~ProxyClient(){
}

void ProxyClient::attend(){
    Receiver receiver(socketAccepted, *this);
    receiver.run();
    if(!validClient)return;
    vm.disconnectClient(clientName);
    std::cout << "CLIENT DISCONNECTED: " << clientName << std::endl;
}

void ProxyClient::recieveEvent(std::string event){
    std::cout << "RECEIVED FROM: " << clientName << " EVENT: " << event << std::endl;
    json eventJ = json::parse(event);
    EventHandler* eventHandler = eventHandlerSelector.get_event_handler(eventJ["evento"]);
    if(eventHandler != nullptr)
        eventHandler->handle(eventJ);
}

bool ProxyClient::isExecuting(){
	return executing;
}

void ProxyClient::sendEvent(std::string event){
    std::cout << "SENDING TO: " << clientName << " EVENT: " << event << std::endl;
    char* eventToSend = (char*)event.c_str();
    uint32_t tamanio_32 = (uint32_t)htonl(strlen(eventToSend) + 1);
    socketAccepted.enviar((char*)(&tamanio_32), sizeof(tamanio_32));
    socketAccepted.enviar(eventToSend, strlen(eventToSend) + 1);
}