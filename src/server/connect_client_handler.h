#ifndef JSON_LIB
#define JSON_LIB
#include "../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef SELFTP_CONNECT_CLIENT_HANDLER_H
#define SELFTP_CONNECT_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

class ConnectClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    ConnectClientHandler(ServerHandler* server_handler);
    ~ConnectClientHandler();
};

#endif
