#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <string>

#include "../common/thread.h"
#include "proxy_client.h"
#include "../common/socket.h"
#include "virtualmachine.h"

/*Clase encargada de aceptar clientes nuevos que se quieran conectar
 * al servidor, hereda de Thread.
 * Tiene el socket del servidor
 * Un vector de punteros a los clientes
 * Un valor booleano que indica si tiene que seguir aceptando nuevos clientes
 * Y una referencia al modelo que se encarga de resolver peticiones de los
 * clientes*/
class Accepter : public Thread {
    Socket socket;
    std::vector<ProxyClient *> clients;
    bool keepAcceptingClients;
    VirtualMachine& vm;
    /*Metodo privado que elimina los clientes que ya fueron atendidos*/
    void deleteClients();

public:
    /*Constructor del aceptador recibe un puerto de donde va a crear el socket
     * y recibe los clientes nuevos, y la referencia al modelo*/
    Accepter(std::string& port, VirtualMachine &vm);
    /*Destructor del aceptador*/
    ~Accepter();
    /*Metodo que cuando se ejecuta el aceptador esta listo para aceptar
     * nuevos clientes*/
    void accept();
    /*Metodo que le indica al aceptador que tiene que dejar de aceptar nuevos
     * clientes*/
    void stop();
    /*Redifinicion del metodo run de Thread corre el metodo aceptar
     * del Accepter*/
    void run() { this->accept(); }
};

#endif
