#ifndef THREAD_H
#define THREAD_H

#include <thread>

/*Clase Thread, encapsula los comportamientos del Thread*/
class Thread {
private:
    std::thread thread;

public:
    Thread() {}

    void start();

    void join();

    /*Metodo virtual puro a redefinir en clases hijas
     * que va a ser ejecutado cuando se lance el hilo*/
    virtual void run() = 0;

    /*Destructor*/
    virtual ~Thread() {}

private:
    /*Forzamos a que los hilos no se puedan copiar*/
    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

    /*Constructor por movimiento*/
    Thread(Thread &&other);

    /*Operador asignacion por movimiento*/
    Thread &operator=(Thread &&other);
};

#endif
