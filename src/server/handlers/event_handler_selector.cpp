#include "event_handler_selector.h"
#include <string>
#include "event_handler.h"
#include "server_handler.h"

#include "connect_client_handler.h"
#include "initialize_client_handler.h"
#include "choose_lobby_client_handler.h"
#include "move_morph_client_handler.h"
#include "get_client_handler.h"
#include "do_client_handler.h"
#include "change_name_client_handler.h"
#include "dismiss_client_handler.h"

#define CONNNECT_EVENT "conectar cliente"
#define INITIALIZE_EVENT "inicializar"
#define CHOOSE_LOBBY_EVENT "elegir lobby"
#define MOVE_MORPH_EVENT "mover morph"
#define GET_EVENT "get"
#define DO_EVENT "do"
#define CHANGE_NAME_EVENT "change name"
#define DISMISS_EVENT "dismiss"

EventHandlerSelector::EventHandlerSelector(ServerHandler *server_handler) : server_handler(server_handler) {
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (CONNNECT_EVENT, new ConnectClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (INITIALIZE_EVENT, new InitializeClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (CHOOSE_LOBBY_EVENT, new ChooseLobbyClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (MOVE_MORPH_EVENT, new MoveMorphClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (GET_EVENT, new GetClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (DO_EVENT, new DoClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (CHANGE_NAME_EVENT, new ChangeNameClientHandler(server_handler)));
    event_handlers.insert(std::pair<std::string, EventHandler *>
                                  (DISMISS_EVENT, new DismissClientHandler(server_handler)));
}

EventHandlerSelector::~EventHandlerSelector() {
    delete server_handler;
    for(auto itEventHanler = event_handlers.begin(); itEventHanler != event_handlers.end(); itEventHanler++){
        delete itEventHanler->second;
    }
}

EventHandler* EventHandlerSelector::get_event_handler(const std::string &event) {
    auto itEvent = event_handlers.find(event);
    if(itEvent != event_handlers.end()){
        return event_handlers.at(event);
    }
    else{
        return nullptr;
    }

}