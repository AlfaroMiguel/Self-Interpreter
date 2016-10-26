#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include "socket.h"
#include "comunicador_cliente.h"
#include "thread.h"
#include <vector>

/* Clase que se ocupa de atender clientes.*/
class Aceptador: public Thread{
 private:
  std::vector<ComunicadorCliente*> clientes;
  Socket& skt_server;
  //Modelo& modelo;
  bool aceptando;

  void run(){
	  this->aceptar();
  }

  /* Espera que termine la ejecucion de todos los clientes
   * y los elimina. */
  void terminar();
  /* Elimina todos los clientes que ya hayan terminado su ejecucion */
  void limpiar_clientes();

 public:
  /* Constructor de la clase. Recibe una referencia al socket principal
   * del server para poder aceptar clientes, un puerto para asociarlo
   * y una referencia al modelo para referenciarlo a los clientes aceptados. */
  Aceptador(Socket& skt_server, const char* puerto);
  /* Destructor de la clase. */
  ~Aceptador();
  /* Acepta clientes mientras se encuentre conectado el socket
   * del servidor */
  void aceptar();
  void operator()(){
	  this->run();
  }
};

#endif
