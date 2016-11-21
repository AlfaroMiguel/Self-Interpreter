#include "accepter.h"
#include <string>
#include <vector>

/*//Template del remove_if si hacia el include<algorithm> rompia el SERCOM
template <class ForwardIterator, class UnaryPredicate>
ForwardIterator remove_if(ForwardIterator first,
                           ForwardIterator last,
                           UnaryPredicate pred)
{
    ForwardIterator result = first;
    while (first!=last) {
        if (!pred(*first)) {
            *result = std::move(*first);
            ++result;
        }
        ++first;
    }
    return result;
}*/

//Funcion que nos indica si un client tiene que ser eliminado
bool deleteClient(ProxyClient *client){
    return client == NULL;
}

Accepter::Accepter(std::string& port, VirtualMachine& vm) :
        keepAcceptingClients(true),
        vm(vm){
    socket.bind_and_listen(port);
}

Accepter::~Accepter() {}

void Accepter::deleteClients() {
    std::vector<int> clientsToDelete;
    for (unsigned int i = 0; i < clients.size(); i++) {
        if (!(clients[i]->isExecuting())) {
            clients[i]->join();
            delete clients[i];
            clients[i] = NULL;
        }
    }
    clients.erase(remove_if(clients.begin(),
                             clients.end(),
                             deleteClient),
                                  clients.end());
}

void Accepter::accept() {
    while (keepAcceptingClients) {
        Socket socket_acpt;
        try { socket.aceptar(socket_acpt); }
        catch (const SocketError &e) {
            keepAcceptingClients = false;
            continue;
        }
        std::cerr << "Cliente conectado." << std::endl;
        ProxyClient *newClient = new ProxyClient(std::move(socket_acpt), vm);
        newClient->start();
        deleteClients();
        clients.push_back(newClient);
    }
    for (ProxyClient *client: clients) {
        client->join();
        delete client;
    }
}

void Accepter::stop() {
    socket.shutdown();
}
