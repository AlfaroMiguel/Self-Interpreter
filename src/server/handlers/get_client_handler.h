#ifndef JSON_LIB
#define JSON_LIB
#include "../../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef GET_CLIENT_HANDLER_H
#define GET_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

/*EventHandler que representa el handler del evento que el cliente envio codigo Self
 * con el metodo GET de Self*/
class GetClientHandler : public EventHandler{
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);
public:
    /*Creador del handler recibe un puntero al Server Handler*/
    GetClientHandler(ServerHandler* server_handler);
    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~GetClientHandler();
};

#endif
