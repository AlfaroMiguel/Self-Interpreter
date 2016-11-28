#ifndef JSON_LIB
#define JSON_LIB
#include "../../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef INITIALIZE_CLIENT_HANDLER_H
#define INITIALIZE_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"
/*EventHandler que representa el handler del evento cuando un cliente se conecta y hace un
 * request de la informacion disponible para ese cliente*/
class InitializeClientHandler : public EventHandler{
private:
    /*Recibe el json representando el evento y lo resuelve*/
    void handle(json j);
public:
    /*Creador del handler recibe un puntero al Server Handler*/
    InitializeClientHandler(ServerHandler* server_handler);
    /*Destructor no libera ningun recuso al no adquirir ninguno en el constructor*/
    ~InitializeClientHandler();
};

#endif
