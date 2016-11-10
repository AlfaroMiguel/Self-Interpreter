#ifndef CONTROLADOR_EVENTOS_H
#define CONTROLADOR_EVENTOS_H

#include <string>

class ComunicadorCliente;

class ControladorDeEventos {
private:
    ComunicadorCliente& cliente;

public:
    ControladorDeEventos(ComunicadorCliente& cliente);
    ~ControladorDeEventos();
    void resolverEvento(std::string evento);
};


#endif
