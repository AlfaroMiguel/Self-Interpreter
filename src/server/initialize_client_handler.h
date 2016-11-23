#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef INITIALIZE_CLIENT_HANDLER_H
#define INITIALIZE_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

class InitializeClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    InitializeClientHandler(ServerHandler* server_handler);
    ~InitializeClientHandler();
};

#endif
