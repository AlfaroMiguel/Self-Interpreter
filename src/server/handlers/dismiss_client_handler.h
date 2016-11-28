#ifndef DISMISS_CLIENT_HANDLER_H
#define DISMISS_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

class DismissClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    DismissClientHandler(ServerHandler* server_handler);
    ~DismissClientHandler();
};

#endif
