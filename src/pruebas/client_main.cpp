#include <iostream>
#include "comunicador_server.h"
#include <string>
#define POS_HOSTNAME 1
#define POS_PUERTO 2
#define SALIDA 0

int main(int argc, const char* argv[]){
	try{
		std::string hostname(argv[POS_HOSTNAME]);
		std::string puerto(argv[POS_PUERTO]);
		ComunicadorServer comunicadorServer(hostname, puerto);
		std::string mensaje("a");
		comunicadorServer.ejecutar_mensaje(mensaje);
		return 0;
	}
	catch(const std::exception& error) {
		std::cout << error.what() << std::endl;
		return SALIDA;
	}
}
