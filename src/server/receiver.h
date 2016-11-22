#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "proxy_client.h"
/*Recibidor que corre en su propio hilo
 * Se encarga de recibir los eventos del cliente
 * y notificarlos al proxy cliente*/
class Receiver: public Thread{
 public:
	/*Recibe una referencia a un socket, y al proxy cliente*/
  Receiver(Socket& skt, ProxyClient& client);
	/*Destructor*/
  ~Receiver();
	/*Redefinicion del metodo run del Thread, pone a recibir indefinidamente
	 * al recibidor*/
  void run() {
	  receive();
  }
 private:
  	Socket& skt;
  	ProxyClient& client;
  	bool isReceiving;
  	void receive();
};
#endif
