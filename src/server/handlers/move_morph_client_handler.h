#ifndef MOVE_MORPH_CLIENT_HANDLER_H
#define MOVE_MORPH_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

class MoveMorphClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    MoveMorphClientHandler(ServerHandler* server_handler);
    ~MoveMorphClientHandler();
};

#endif
