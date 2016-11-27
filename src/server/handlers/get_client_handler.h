#ifndef JSON_LIB
#define JSON_LIB
#include "../../common/json.hpp"
using json = nlohmann::json;
#endif

#ifndef GET_CLIENT_HANDLER_H
#define GET_CLIENT_HANDLER_H

#include "event_handler.h"
#include "server_handler.h"

class GetClientHandler : public EventHandler{
private:
    void handle(json j);
public:
    GetClientHandler(ServerHandler* server_handler);
    ~GetClientHandler();
};

#endif
