#ifndef RECIBIDOR_H
#define RECIBIDOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "proxy_client.h"

class Receiver: public Thread{
 public:
  Receiver(Socket& skt, ProxyClient& client);
  ~Receiver();
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
