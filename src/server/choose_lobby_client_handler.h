#ifndef CHOOSE_LOBBY_CLIENT_HANDLER_H
#define CHOOSE_LOBBY_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"
#include "../common/json.hpp"

class ChooseLobbyClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    ChooseLobbyClientHandler(ServerHandler* server_handler);
    ~ChooseLobbyClientHandler();
};

#endif