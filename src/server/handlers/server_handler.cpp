#include "server_handler.h"

#include "../proxy_client.h"
#include "../../common/json.hpp"

using json = nlohmann::json;

ServerHandler::ServerHandler(ProxyClient& client) : client(client){}

ServerHandler::~ServerHandler(){}

void ServerHandler::connect(const std::string& clientName){
    std::cout << " Se conecta cliente " << clientName << std::endl; //TODO sacar debug
    bool clientIsConnected = client.vm.connectClient(clientName, &client);
    json jResponse;
    if(clientIsConnected){
        jResponse["evento"] = "cliente conectado";
        client.clientName = clientName;
        client.validClient = true;
    }
    else
        jResponse["evento"] = "error";

    client.sendEvent(jResponse.dump());
}

void ServerHandler::initialize(){
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

void ServerHandler::chooseLobby(const std::string& lobbyName, const std::string& lobbyState){
    //Conecto al client al lobby
    if(lobbyState == "compartido")
        client.vm.connectClientToLobby(client.clientName, lobbyName, true);
    else
        client.vm.connectClientToLobby(client.clientName, lobbyName, false);

    json jDatosLobby;
    jDatosLobby["evento"] = "datos lobby";
    client.sendEvent(jDatosLobby.dump());
}

void ServerHandler::moveMorph(int idMorph, double newX, double newY) {
    client.vm.clientMovedMorph(client.clientName, idMorph, newX, newY);
}

void ServerHandler::interpretSelfGet(const std::string& code, int morphID){
    client.vm.interpretCodeGet(client.clientName, code, morphID);
}

void ServerHandler::interpretSelfDo(const std::string& code, int morphID){
    client.vm.interpretCodeDo(client.clientName, code, morphID);
}

void ServerHandler::changeObjectName(int objectID, const std::string& newName){
    client.vm.changeObjectName(client.clientName, objectID, newName);
}