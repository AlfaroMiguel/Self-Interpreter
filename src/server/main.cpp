#include <iostream>
#include "../common/socket.h"
#include "aceptador.h"

#define SALIDA 0
#define POS_PORT 1
#define CANT_PARAMETROS 2
#define CARACTER_SALIR "q"

int main(int argc, const char *argv[]) try{
    if(argc != CANT_PARAMETROS){
        return SALIDA;
    }
    std::string puerto = argv[POS_PORT];
    Aceptador aceptador(puerto);
    aceptador.run();
    std::string entrada;
    while (getline(std::cin, entrada)) {
        std::cerr << entrada << std::endl;
        if (entrada == CARACTER_SALIR) {
            aceptador.parar();
            aceptador.join();
            break;
        }
    }
    return 0;
}
catch(...){
    return SALIDA;
}