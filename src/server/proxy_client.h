#ifndef JSON_LIB
#define JSON_LIB

#include "../common/json.hpp"

using json = nlohmann::json;
#endif

#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "../common/socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "../common/thread.h"
#include "virtualmachine/virtualmachine.h"

#include "handlers/event_handler_selector.h"

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del client.
 * Corre en su propio Thread, tiene al socket resultado de aceptar al cliente
 * Un valor boleano que indica si se encuentra ejecutandose
 * Un EventHandlerSelector para resolver los diferentes eventos ocurridos
 * Una referencia a la Virtual Machine para realizar los diferentes pedidos por parte del cliente*/
class ProxyClient : public Thread {
private:
    Socket socketAccepted;
    bool executing;
    void attend();
    EventHandlerSelector eventHandlerSelector;
    bool validClient;
    std::string clientName;
    VirtualMachine &vm;
    friend class ServerHandler;
    friend class Receiver;
public:
    /*Constructor del proxy cliente recibe un socket y una referencia a la VirtualMachine*/
    ProxyClient(Socket socketAccepted, VirtualMachine &vm);

    /* Destructor de la clase. */
    virtual ~ProxyClient();

    /* Devuelve true si aun no termino su ejecucion y false en caso de
     * haber finalizado. */
    bool isExecuting();

    void run() {
        this->attend();
    }

    void operator()() {
        this->run();
    }
    /*Metodo que recibe una cadena en formato json desde el reciever y es resuelto*/
    void recieveEvent(std::string event);

    /*Recibe una cadena en formato json y es enviado al cliente*/
    void sendEvent(std::string event);
};

#endif
