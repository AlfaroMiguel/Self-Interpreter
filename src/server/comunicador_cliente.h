#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "../common/socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "../common/thread.h"
#include "controlador_eventos.h"

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del cliente. */
class ComunicadorCliente : public Thread {
private:
    Socket skt_aceptar;
    bool ejecutando;
    void atender();
    ControladorDeEventos controladorDeEventos;

public:
    ComunicadorCliente(Socket skt_aceptar);

    /* Destructor de la clase. */
    virtual ~ComunicadorCliente();
    /* Devuelve true si aun no termino su ejecucion y false en caso de
     * haber finalizado. */
    bool esta_ejecutando();

    void run() {
        this->atender();
    }

    void operator()() {
        this->run();
    }

    void recibirEvento(std::string evento);
    void enviarEvento(std::string evento);
};

#endif
