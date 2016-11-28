#ifndef JSON_LIB
#define JSON_LIB

#include "../../common/json.hpp"

using json = nlohmann::json;
#endif

#ifndef DO_CLIENT_HANDLER_H
#define DO_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que el cliente envio codigo Self
 * con el metodo DO*/
class DoClientHandler : public EventHandler {
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);

public:
    /*Creador del handler recibe un puntero al Server Handler*/
    DoClientHandler(ServerHandler *server_handler);

    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~DoClientHandler();
};

#endif
