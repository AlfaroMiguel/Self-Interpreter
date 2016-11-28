#ifndef SELFTP_CHANGE_NAME_H
#define SELFTP_CHANGE_NAME_H

#include "event_handler.h"
#include "server_handler.h"

class ChangeNameClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    ChangeNameClientHandler(ServerHandler* server_handler);
    ~ChangeNameClientHandler();
};

#endif
