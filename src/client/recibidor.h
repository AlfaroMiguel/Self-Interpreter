#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "server_proxy.h"

class Recibidor: public Thread{
 public:
  Recibidor(Socket& skt, ServerProxy& server_proxy);
  ~Recibidor();
  void run() {
	  recibir();
  }
  bool is_active();
 private:
  	Socket& skt;
  	ServerProxy& server_proxy;
  	bool active;
  	void recibir();
};
#endif