#include "event_handler.h"
#include "proxy_client.h"
#include "../common/json.hpp"

using json = nlohmann::json;

EventHandler::EventHandler(ProxyClient& client) : client(client){}

EventHandler::~EventHandler(){}

void EventHandler::connect(std::string clientName){
    std::cout << " Se conecta cliente " << clientName << std::endl; //TODO sacar debug
    bool clientIsConnected = client.vm.connectClient(clientName, &client);
    json jResponse;
    if(clientIsConnected){
        jResponse["evento"] = "cliente conectado";
        client.clientName = clientName;
    }
    else
        jResponse["evento"] = "error";

    client.sendEvent(jResponse.dump());
}

void EventHandler::initialize(){
    std::vector<std::string> lobbies = client.vm.getAvailablesLobbies(client.clientName);
    json jlobbies;
    for(int i = 0; i < lobbies.size(); i++){
        jlobbies[std::to_string(i)] = lobbies[i];
    }
    json jInitialize;
    jInitialize["evento"] = "agregar lobbies";
    jInitialize["lobbies"] = jlobbies.dump();
    client.sendEvent(jInitialize.dump());
}

void EventHandler::chooseLobby(std::string lobbyName, std::string lobbyState){
    //Conecto al client al lobby
    if(lobbyState == "compartido")
        client.vm.connectClientToLobby(client.clientName, lobbyName, true);
    else
        client.vm.connectClientToLobby(client.clientName, lobbyName, false);

    json jDatosLobby;
    jDatosLobby["evento"] = "datos lobby";
    client.sendEvent(jDatosLobby.dump());
}

void EventHandler::moveMorph(int idMorph, double newX, double newY) {
    client.vm.clientMovedMorph(client.clientName, idMorph, newX, newY);
}

void EventHandler::interpretSelfGet(std::string code){
    client.vm.interpretCodeGet(client.clientName, code);
}

void EventHandler::interpretSelfDo(std::string code){
    client.vm.interpretCodeDo(client.clientName, code);
}

void EventHandler::handleEvent(std::string event) { //TODO implementar un map para los eventos
    json eventJ = json::parse(event);
    std::cout << eventJ["evento"] << std::endl; //Aca dependiendo del event envio o modifico cosas

    std::string eventName = eventJ["evento"];

    if(eventName == "conectar cliente"){ //El client me informa su objectName
        connect(eventJ["nombre"]);
    }

    if(eventName == "inicializar"){ //El client quiere los lobbys
        initialize();
    }

    if(eventName == "elegir lobby"){ //EL client elijio un lobby
        chooseLobby(eventJ["lobby"], eventJ["estado"]);
    }
    if(eventName == "mover morph"){ //Se movio un morph
        moveMorph(eventJ["id"], eventJ["x"], eventJ["y"]);
    }
    if (eventName == "get"){//Enviaron codigo y quieren ver los morphs
        interpretSelfGet(eventJ["codigo"]);
    }
    if(eventName == "do"){
        interpretSelfDo(eventJ["codigo"]);
    }

}
