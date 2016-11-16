#ifndef CONTROLADOR_EVENTOS_H
#define CONTROLADOR_EVENTOS_H

#include <string>
class ComunicadorCliente;

class ControladorDeEventos {
private:
    ComunicadorCliente& cliente;

    void resolverConectar(std::string nombre);
    void resolverInicializar();
    void resolverElegirLobby(std::string nombreLobby, std::string estadoLobby);

public:
    ControladorDeEventos(ComunicadorCliente& cliente);
    ~ControladorDeEventos();
    void resolverEvento(std::string evento);
};


#endif
