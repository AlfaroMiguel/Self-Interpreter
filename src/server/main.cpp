#include "../common/json.hpp"
using json = nlohmann::json;

#include <iostream>
#include "../common/socket.h"
#include "accepter.h"

#include <iostream>
#include <fstream>

#define RET_EXIT 0
#define POS_PORT 1
#define MIN_PARAM 2

#define EXIT "sht"
#define SERIALIZATION "ser"
#define DEL_SERIALIZATION_FILE "del"

#define SERIALIZATION_FILE "server.txt"

#define SH_MSG "Ingrese 'sht' si se quiere cerrar el servidor sin persistencia"
#define SER_MSG "Ingrese 'ser' si se quiere cerrar el servidor con persistencia"
#define DEL_MSG "Ingrese 'del' si se quiere eliminar la persistencia"

int main(int argc, const char *argv[]) try{
    if(argc != MIN_PARAM){
        return RET_EXIT;
    }

    std::ifstream jsonFile (SERIALIZATION_FILE);
    std::string linea;
    std::string jsonString;
    if (jsonFile.is_open()) {
        while ( getline (jsonFile,linea))jsonString.append(linea);
        jsonFile.close();
    }

    VirtualMachine* vm;

    if(jsonString != ""){
        std::cout << "Voy a serializar" << std::endl;
        json jSerialization = json::parse(jsonString);
        vm = VirtualMachine::deserialize(jSerialization);

    }
    else{
        vm = new VirtualMachine();
        vm->initialize();
    }

    std::cout << "Termino de crearse la VirtualMachine" << std::endl; //TODO debug

    std::string puerto = argv[POS_PORT];
    Accepter aceptador(puerto, *vm);
    aceptador.start();
    std::string entrada;
    while (getline(std::cin, entrada)) {
        if (entrada == EXIT) {
            aceptador.stop();
            aceptador.join();
            break;
        }
        else if(entrada == SERIALIZATION){
            std::cerr << "Serializando Virtual Machine" << std::endl;
            aceptador.stop();
            aceptador.join();
            json jserialize;
            (*vm).serialize(jserialize);

            std::cout << jserialize.dump(4) << std::endl;

            std::ofstream out(SERIALIZATION_FILE);
            out << jserialize.dump();
            out.close();
            break;
        }else if(entrada == DEL_SERIALIZATION_FILE){
            if(remove(SERIALIZATION_FILE) != 0 )
                std::cerr << "Error eliminando el archivo de persistencia" << std::endl;
            else
                std::cerr << "Archivo de persistencia eliminado exitosamente" << std::endl;
            aceptador.stop();
            aceptador.join();
            break;
        }
        else {
            std::cout << SH_MSG << std::endl;
            std::cout << SER_MSG << std::endl;
            std::cout << DEL_MSG << std::endl;
        }
    }
    return RET_EXIT;
}
catch(...){
    return RET_EXIT;
 }
