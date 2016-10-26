#ifndef COMUNICADOR_CLIENTE_H
#define COMUNICADOR_CLIENTE_H

#include "socket.h"
#include <string>
#include <vector>
#include <iostream>
#include "thread.h"

/* Clase que encapsula el manejo del envío y recepción de datos
 * respetando el protocolo correspondiente por parte del cliente. */
class ComunicadorCliente: public Thread{
 private:
  Socket& skt_aceptar;
  //Modelo& modelo;
  bool ejecutando;

  void recibir_mensaje();
  void run(){
	  recibir_mensaje();
  }
 public:
  ComunicadorCliente(Socket& skt_aceptar);
  /* Destructor de la clase. */
  virtual ~ComunicadorCliente();
  /* Devuelve true si aun no termino su ejecucion y false en caso de
   * haber finalizado. */
  bool esta_ejecutando();
  void operator()(){
	  this->run();
  }
};

#endif