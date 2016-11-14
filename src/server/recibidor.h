#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "comunicador_cliente.h"

class Recibidor: public Thread{
 public:
  Recibidor(Socket& skt, ComunicadorCliente& com_cliente);
  ~Recibidor();
  void run() {
	  recibir();
  }
 private:
  	Socket& skt;
  	ComunicadorCliente& com_cliente;
  	bool esta_recibiendo;
  	void recibir();
};
#endif
