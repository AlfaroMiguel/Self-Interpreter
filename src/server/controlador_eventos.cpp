#include "controlador_eventos.h"
#include "comunicador_cliente.h"
#include "../common/json.hpp"

using json = nlohmann::json;

ControladorDeEventos::ControladorDeEventos(ComunicadorCliente& cliente) : cliente(cliente){}

ControladorDeEventos::~ControladorDeEventos(){}

void ControladorDeEventos::resolverConectar(std::string nombre){
    std::cout << " Nuevo cliente " << nombre << std::endl; //Sacar
    json jrespuesta;
    jrespuesta["evento"] = "cliente conectado";
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

void ControladorDeEventos::resolverEvento(std::string evento) {
    json eventoj = json::parse(evento);
    std::cout << eventoj["evento"] << std::endl; //Aca dependiendo del evento envio o modifico cosas

    std::string nombreEvento = eventoj["evento"];

    if(nombreEvento == "conectar cliente"){ //El cliente me informa a que lobby se conecta
        resolverConectar(eventoj["nombre"]);
    }

    if(nombreEvento == "inicializar"){
        resolverInicializar();
    }

    if(nombreEvento == "mover morph"){
        std::cout << "El morph " << eventoj["nombre"] << "se movio a x:" << eventoj["x"] << " y:" << eventoj["y"] << std::endl;
        //Aca tengo que actualizar las posiciones de los morphs
    }

}
