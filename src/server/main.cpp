
//Descomentar si se quiere probar el main del parser
/*#include "parser/interpreter.h"


int main(int argc, char const *argv[]) {
    Object* lobby = new Object;
    Interpreter interpreter(lobby,nullptr);
    std::cout << "pepe" << std::endl;
    char shellCode[] = "lobby _AddSlots: (| shell = (|  |).  |)."; //devuelve el ptr de shell
    char createNullObject[] = "lobby _AddSlots: (| punto3 = (|  |).  |)."; //devuelve el ptr de punto
    char createNullObject1[] = "lobby _AddSlots: (| punto1 = (|  |).  |)."; //devuelve el ptr de punto1
    char createNullObject2[] = "lobby _AddSlots: (| punto2 = (|  |).  |)."; //devuelve el ptr de punto2
    interpreter.interpretChar(shellCode);
    interpreter.interpretChar(createNullObject);
    interpreter.interpretChar(createNullObject1);
    interpreter.interpretChar(createNullObject2);
    char punto[] = "lobby _AddSlots: (| punto = (| x = 5. y = 3. |).  |). \n\0\0"; //devuelve el ptr de punto
    interpreter.interpretChar(punto);
    char algunMetodo[] = "punto xPorDos.\n\0\0";
    interpreter.interpretChar(algunMetodo);
    char pajaro[] = "lobby _AddSlots: (| pajaro = (| x = 1. y = 3. algunMetodo = (|  | 3 * 2 + 1. ). |).  |). \n\0\0"; //devuelve el ptr de pajaro
    interpreter.interpretChar(pajaro);
    char multiLinea[] = "lobby _AddSlots: (| OtroObjeto = (|x = 1. y <- 3. metodo = (|  | 4 + 2 + 1. ).|).|). lobby _AddSlots: (| OtroObjeto1 = (|x = 1. y <- 3. metodo = (|  | 4 + 2 + 1. ).|).|).";
    interpreter.interpretChar(multiLinea); //devuelve otroObjeto ptr y OtroObjeto1 ptr

    return 0;
} */



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
    VirtualMachine vm;
    std::string puerto = argv[POS_PORT];
    Aceptador aceptador(puerto, vm);
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
