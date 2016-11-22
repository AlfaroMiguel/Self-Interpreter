#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "../common/socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "../common/thread.h"
#include "virtualmachine.h"

#include "event_handler_selector.h"
#include "../common/json.hpp"
using json = nlohmann::json;
/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del client. */
class ProxyClient : public Thread {
private:
    Socket socketAccepted;
    bool executing;
    void attend();
    EventHandlerSelector eventHandlerSelector;


public:
    std::string clientName;
    VirtualMachine& vm;

    ProxyClient(Socket socketAccepted, VirtualMachine& vm);

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

    void recieveEvent(std::string event);
    void sendEvent(std::string event);
};

#endif
