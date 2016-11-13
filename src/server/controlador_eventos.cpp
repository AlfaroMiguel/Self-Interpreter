#include "controlador_eventos.h"
#include "comunicador_cliente.h"
#include "../common/json.hpp"

using json = nlohmann::json;

ControladorDeEventos::ControladorDeEventos(ComunicadorCliente& cliente) : cliente(cliente){}

ControladorDeEventos::~ControladorDeEventos(){}

void ControladorDeEventos::resolverInicializar(){
    std::string lobby1("Lobby principal");
    std::string lobby2("Lobby secundario");
    std::string lobby3("Lobby backup");
    //Hardcodeo los lobbys pero se los tengo que pedir al modelo
    std::vector<std::string> lobbys;
    lobbys.push_back(lobby1);
    lobbys.push_back(lobby2);
    lobbys.push_back(lobby3);

    for(int i = 0; i < lobbys.size(); i++){
        json jrespuesta;
        jrespuesta["evento"] = "agregar lobby";
        jrespuesta["id"] = lobbys[i];
        cliente.enviarEvento(jrespuesta.dump());
    }
    json jrespuesta;
    jrespuesta["evento"] = "iniciar";
    cliente.enviarEvento(jrespuesta.dump());
}

void ControladorDeEventos::resolverConectar(std::string nombre, std::string lobby){
    std::cout << nombre<< " se quiere conectar a " << lobby << std::endl; //Sacar
    json jrespuesta;
    jrespuesta["evento"] = "cliente conectado";
    cliente.enviarEvento(jrespuesta.dump());
}

void ControladorDeEventos::resolverEvento(std::string evento) {
    json eventoj = json::parse(evento);
    std::cout << eventoj["evento"] << std::endl; //Aca dependiendo del evento envio o modifico cosas

    std::string nombreEvento = eventoj["evento"];

    if(nombreEvento == "inicializar"){ //Ni bien se conecta el cliente le paso los lobbys disponibles
        resolverInicializar();
    }

    if(nombreEvento == "conectar"){ //El cliente me informa a que lobby se conecta
        resolverConectar(eventoj["nombre"], eventoj["lobby"]);
    }

    if(nombreEvento == "mover morph"){
        std::cout << "El morph " << eventoj["nombre"] << "se movio a x:" << eventoj["x"] << " y:" << eventoj["y"] << std::endl;
        //Aca tengo que actualizar las posiciones de los morphs
    }

}
