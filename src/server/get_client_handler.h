#ifndef GET_CLIENT_HANDLER_H
#define GET_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"
#include "../common/json.hpp"

class GetClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    GetClientHandler(ServerHandler* server_handler);
    ~GetClientHandler();
};

#endif
