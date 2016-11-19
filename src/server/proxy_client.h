#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "../common/socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "../common/thread.h"
#include "controlador_eventos.h"
#include "virtualmachine.h"

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del cliente. */
class ProxyClient : public Thread {
private:
    Socket socketAccepted;
    bool executing;
    void atender();
    ControladorDeEventos controladorDeEventos;


public:
    std::string clientName;
    VirtualMachine& vm;

    ProxyClient(Socket skt_aceptar, VirtualMachine& vm);

    /* Destructor de la clase. */
    virtual ~ProxyClient();
    /* Devuelve true si aun no termino su ejecucion y false en caso de
     * haber finalizado. */
    bool isExecuting();

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