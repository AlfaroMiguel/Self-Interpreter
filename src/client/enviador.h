#ifndef ENVIADOR_H
#define ENVIADOR_H

#include "../common/thread.h"

class Enviador: public Thread{
 public:
  Enviador();
  ~Enviador();
};
#endif