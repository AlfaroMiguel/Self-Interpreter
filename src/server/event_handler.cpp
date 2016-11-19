#include "controlador_eventos.h"
#include "proxy_client.h"
#include "../common/json.hpp"

using json = nlohmann::json;

EventHandler::EventHandler(ProxyClient& cliente) : client(cliente){}

EventHandler::~EventHandler(){}

void EventHandler::connect(std::string clientName){
    std::cout << " Se conecta client " << clientName << std::endl;
    bool sePudoConectar = client.vm.connectClient(clientName, &client);
    json jrespuesta;
    if(sePudoConectar){
        jrespuesta["evento"] = "client conectado";
        client.clientName = clientName;
    }
    else
        jrespuesta["evento"] = "error";

    client.sendEvent(jrespuesta.dump());
}

void EventHandler::initialize(){
    std::vector<std::string> lobbies = client.vm.getAvailablesLobbies(client.clientName);
    json jlobbies;
    for(int i = 0; i < lobbies.size(); i++){
        jlobbies[std::to_string(i)] = lobbies[i];
    }
    json jInicializar;
    jInicializar["evento"] = "agregar lobbies";
    jInicializar["lobbies"] = jlobbies.dump();
    client.sendEvent(jInicializar.dump());
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

void EventHandler::handleEvent(std::string event) {
    json eventoj = json::parse(event);
    std::cout << eventoj["event"] << std::endl; //Aca dependiendo del event envio o modifico cosas

    std::string nombreEvento = eventoj["event"];

    if(nombreEvento == "conectar client"){ //El client me informa su nombre
        connect(eventoj["nombre"]);
    }

    if(nombreEvento == "inicializar"){ //El client quiere los lobbys
        initialize();
    }

    if(nombreEvento == "elegir lobby"){ //EL client elijio un lobby
        chooseLobby(eventoj["lobby"], eventoj["estado"]);
    }
    if(nombreEvento == "mover morph"){ //Se movio un morph
        moveMorph(eventoj["id"], eventoj["x"], eventoj["y"]);
    }
    if (nombreEvento == "get"){//Enviaron codigo y quieren ver los morphs
        interpretSelfGet(eventoj["codigo"]);
    }
    if(nombreEvento == "do"){
        interpretSelfDo(eventoj["codigo"]);
    }

}
