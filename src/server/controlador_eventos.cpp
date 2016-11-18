#include "controlador_eventos.h"
#include "comunicador_cliente.h"
#include "../common/json.hpp"

using json = nlohmann::json;

ControladorDeEventos::ControladorDeEventos(ComunicadorCliente& cliente) : cliente(cliente){}

ControladorDeEventos::~ControladorDeEventos(){}

void ControladorDeEventos::resolverConectar(std::string nombre){
    std::cout << " Se conecta cliente " << nombre << std::endl;
    bool sePudoConectar = cliente.vm.connectClient(nombre, &cliente);
    json jrespuesta;
    if(sePudoConectar){
        jrespuesta["evento"] = "cliente conectado";
        cliente.clientName = nombre;
    }
    else
        jrespuesta["evento"] = "error";

    cliente.enviarEvento(jrespuesta.dump());
}

void ControladorDeEventos::resolverInicializar(){
    std::vector<std::string> lobbies = cliente.vm.getAvailablesLobbies(cliente.clientName);
    json jlobbies;
    for(int i = 0; i < lobbies.size(); i++){
        jlobbies[std::to_string(i)] = lobbies[i];
    }
    json jInicializar;
    jInicializar["evento"] = "agregar lobbies";
    jInicializar["lobbies"] = jlobbies.dump();
    cliente.enviarEvento(jInicializar.dump());
}

void ControladorDeEventos::resolverElegirLobby(std::string nombreLobby, std::string estadoLobby){
    //Conecto al cliente al lobby
    if(estadoLobby == "compartido")
        cliente.vm.connectClientToLobby(cliente.clientName, nombreLobby, true);
    else
        cliente.vm.connectClientToLobby(cliente.clientName, nombreLobby, false);


    json jDatosLobby;
    jDatosLobby["evento"] = "datos lobby";
    cliente.enviarEvento(jDatosLobby.dump());
}

void ControladorDeEventos::resolverMoverMorph(std::string idMorph, double newX, double newY) {
    cliente.vm.clientMovedMorph(cliente.clientName, idMorph, newX, newY);
}

void ControladorDeEventos::resolverGet(std::string codigo){
    cliente.vm.interpretCodeGet(cliente.clientName, codigo);
}

void ControladorDeEventos::resolverDo(std::string codigo){
    cliente.vm.interpretCodeDo(cliente.clientName, codigo);
}

void ControladorDeEventos::resolverEvento(std::string evento) {
    json eventoj = json::parse(evento);
    std::cout << eventoj["evento"] << std::endl; //Aca dependiendo del evento envio o modifico cosas

    std::string nombreEvento = eventoj["evento"];

    if(nombreEvento == "conectar cliente"){ //El cliente me informa su nombre
        resolverConectar(eventoj["nombre"]);
    }

    if(nombreEvento == "inicializar"){ //El cliente quiere los lobbys
        resolverInicializar();
    }

    if(nombreEvento == "elegir lobby"){ //EL cliente elijio un lobby
        resolverElegirLobby(eventoj["lobby"], eventoj["estado"]);
    }
    if(nombreEvento == "mover morph"){ //Se movio un morph
        resolverMoverMorph(eventoj["id"], eventoj["x"], eventoj["y"]);
    }
    if (nombreEvento == "get"){//Enviaron codigo y quieren ver los morphs
        resolverGet(eventoj["codigo"]);
    }
    if(nombreEvento == "do"){
        resolverDo(eventoj["codigo"]);
    }

}
