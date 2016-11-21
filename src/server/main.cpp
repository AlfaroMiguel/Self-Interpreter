
//Descomentar si se quiere probar el main del parser
/*#include "parser/interpreter.h"


int main(int argc, char const *argv[]) {
  Object* lobby = new Object;
  lobby->setName("lobby");
  Interpreter interpreter(lobby,nullptr);
  std::cout << "pepe" << std::endl;
  char puntoCode[] = "lobby _AddSlots: (| punto = (| x = 5. y = 3. xPorDos = (|  | x * 2. ). |).  |).";
  char xPorDos[] = "punto xPorDos.";
  char puntoCloneCode[] = "lobby _AddSlots: (| punto1 = (| x <- 20. y <- 1. proto* = punto. |). |).";
  char punto1XPorDos[] = "punto1 xPorDos.";
  interpreter.interpretChar(puntoCode);
  interpreter.interpretChar(xPorDos);
  interpreter.interpretChar(puntoCloneCode);
  interpreter.interpretChar(punto1XPorDos);
  return 0;
} */



#include <iostream>
#include "../common/socket.h"
#include "accepter.h"

#define RET_EXIT 0
#define POS_PORT 1
#define MIN_PARAM 2
#define EXIT "shutdown"
#define SERIALIZATION "serialization"

int main(int argc, const char *argv[]) try{
    if(argc != MIN_PARAM){
        return RET_EXIT;
    }

    VirtualMachine vm;

    std::string puerto = argv[POS_PORT];
    Accepter aceptador(puerto, vm);
    aceptador.start();
    std::string entrada;
    while (getline(std::cin, entrada)) {
        std::cerr << entrada << std::endl;
        if (entrada == EXIT) {
            aceptador.stop();
            aceptador.join();
            break;
        }
        else if(entrada == SERIALIZATION){
            std::cerr << "Serializando Virtual Machine" << std::endl;
            aceptador.stop();
            aceptador.join();
            break;
        }
    }
    return RET_EXIT;
}
catch(...){
    return RET_EXIT;
}
