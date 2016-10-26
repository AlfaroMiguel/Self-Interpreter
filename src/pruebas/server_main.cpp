#include <iostream>
#include "socket.h"
#include "comunicador_cliente.h"
#include "thread.h"
#include "aceptador.h"
#include <string>
#include <mutex>
#define POS_PUERTO 1
#define CARACTER_SALIDA "q"
#define SALIDA 0

int main(int argc, const char* argv[]) {
	try {
		Socket skt_server;
		std::string puerto(argv[POS_PUERTO]);
		Aceptador aceptador(skt_server, puerto);
		aceptador.start();

		std::string caracter;
		while(getline(std::cin, caracter))
			if (caracter == CARACTER_SALIDA) {
				skt_server.shutdown();
				aceptador.join();
				break;
			}
		return SALIDA;
	}
	catch(const std::exception& error){
		std::cout << error.what() << std::endl;
		return SALIDA;
	}
}

