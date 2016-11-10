#include "controlador_eventos.h"
#include "comunicador_cliente.h"
#include "../common/json.hpp"

using json = nlohmann::json;

ControladorDeEventos::ControladorDeEventos(ComunicadorCliente& cliente) : cliente(cliente){}

ControladorDeEventos::~ControladorDeEventos(){}

void ControladorDeEventos::resolverEvento(std::string evento) {
    json eventoj = json::parse(evento);
    std::cout << eventoj["evento"] << std::endl; //Aca dependiendo del evento envio o modifico cosas

    std::string nombreEvento = eventoj["evento"];

    if(nombreEvento == "inicializar"){
        std::string lobby1("1");
        std::string lobby2("2");
        std::string lobby3("3");
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
        json j;
        j["evento"] = "iniciar";
        cliente.enviarEvento(j.dump());
    }



}
