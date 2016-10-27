#include <iostream>
#include "../common/socket.h"
#include "aceptador.h"

#define SALIDA 0
#define POS_PORT 1
#define CANT_PARAMETROS 2


int main(int argc, const char *argv[]) try{
    if(argc != CANT_PARAMETROS){
        return SALIDA;
    }
    std::string puerto = argv[POS_PORT];

    Socket socket_server;
    Aceptador aceptador(socket_server, puerto);
    aceptador();

    return 0;
}
catch(...){
    return SALIDA;
}