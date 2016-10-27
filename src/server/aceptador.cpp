#include "aceptador.h"
#include <string>
#include <vector>

//Template del remove_if si hacia el include<algorithm> rompia el SERCOM
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
}

//Funcion que nos indica si un cliente tiene que ser eliminado
bool hay_que_eliminar_cliente(ComunicadorCliente* cliente){
    return cliente == NULL;
}

Aceptador::Aceptador(std::string& puerto) :
        sigo_aceptando(true){
    socket.bind_and_listen(puerto);
}

Aceptador::~Aceptador() {}

void Aceptador::eliminar_clientes_atendidos() {
    std::vector<int> clientes_a_eliminar;
    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (!(clientes[i]->esta_ejecutando())) {
            clientes[i]->join();
            delete clientes[i];
            clientes[i] = NULL;
        }
    }
    clientes.erase(remove_if(clientes.begin(),
                                  clientes.end(),
                                  hay_que_eliminar_cliente),
                                  clientes.end());
}

void Aceptador::aceptar() {
    while (sigo_aceptando) {
        Socket socket_acpt;
        try { socket.aceptar(socket_acpt); }
        catch (const SocketError &e) {
            std::cerr << "Entro aca" << std::endl;
            sigo_aceptando = false;
            continue;
        }
        std::cerr << "Cliente conectado." << std::endl;
        ComunicadorCliente *cliente_nuevo = new ComunicadorCliente(std::move(socket_acpt));
        cliente_nuevo->run();
        eliminar_clientes_atendidos();
        clientes.push_back(cliente_nuevo);
    }
    for (ComunicadorCliente *cliente: clientes) {
        cliente->join();
        delete cliente;
    }
}

void Aceptador::parar() {
    socket.shutdown();
}
