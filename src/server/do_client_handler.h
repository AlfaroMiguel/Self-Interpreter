#ifndef DO_CLIENT_HANDLER_H
#define DO_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"
#include "../common/json.hpp"

class DoClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    DoClientHandler(ServerHandler* server_handler);
    ~DoClientHandler();
};

#endif
