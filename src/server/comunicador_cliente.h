#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "../common/socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "../common/thread.h"

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del cliente. */
class ComunicadorCliente : public Thread {
private:
    Socket skt_aceptar;
    bool ejecutando;

    void recibir_mensaje();

public:
    ComunicadorCliente(Socket skt_aceptar);

    /* Destructor de la clase. */
    virtual ~ComunicadorCliente();
    /* Devuelve true si aun no termino su ejecucion y false en caso de
     * haber finalizado. */
    bool esta_ejecutando();

    void run() {
        recibir_mensaje();
    }

    void operator()() {
        this->run();
    }
};

#endif