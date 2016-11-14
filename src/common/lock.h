#ifndef LOCK_H
#define LOCK_H

#include <mutex>

/*Clase Lock que encapsula el recurso mutex de forma RAII */
class Lock {
private:
    std::mutex &m;
public:
    /*Lockea el mutex*/
    explicit Lock(std::mutex &m);

    /*Desbloquea el mutex cuando se va de scope*/
    ~Lock();

private:
    /*No tiene sentido copian ni mover Locks*/
    Lock(const Lock &) = delete;

    Lock &operator=(const Lock &) = delete;

    Lock(Lock &&) = delete;

    Lock &operator=(Lock &&) = delete;
};

#endif
