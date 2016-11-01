#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "comunicador_server.h"

class Recibidor: public Thread{
 public:
  Recibidor(Socket& skt, ComunicadorServer& com_server);
  ~Recibidor();
  void run() {
	  recibir();
  }
 private:
  	Socket& skt;
  	ComunicadorServer& com_server;
  	bool esta_recibiendo;
  	void recibir();
};
#endif