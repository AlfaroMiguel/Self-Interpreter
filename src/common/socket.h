#ifndef SOCKET_H
#define SOCKET_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "socket_error.h"

/*Definicion de puntero a funcion para poder usar con connect o bind*/
typedef int (*connect_bind_funcion_t)(int socket, const struct sockaddr *addr,
                                      socklen_t addrlen);

/*Clase Socket que encapsula las peticiones al socket, contiene el file
 * descriptor del socket*/
class Socket {
    int fd;

public:
    /*Constructor del socket*/
    Socket();
    /*Destructor del socket*/
    ~Socket();
    /*Eliminamos el constructor por copia*/
    Socket(const Socket &otra) = delete;
    /*Eliminamos el operador asignacion por copia*/
    Socket &operator=(const Socket &otra) = delete;
    /*Constructor por movimiento*/
    Socket(Socket &&otro);
    /*Operador asignacion por movimiento*/
    Socket &operator=(Socket &&otra);
    /*Recibe una cadena con el puerto, luego bindea y escucha en ese puerto*/
    void bind_and_listen(const std::string &puerto);
    /*Recibe una cadena con la ip y el puerto del socket
     * a conectarse y se conecta*/
    void conectar(const std::string &hostname, const std::string &puerto);
    /*Recibe un socket aceptador y acepta un nuevo cliente, luego setea
     * el file descriptor del socket aceptado*/
    void aceptar(Socket &socket_aceptado);
    /*Recibe un buffer con el contenido a enviar y un largo a enviar
     * Envia el contenido del buffer al socket con el que estamos conectados*/
    int enviar(char *buffer, size_t largo);
    /*Recibe un buffer y un largo. Guarda en el buffer 'largo' bytes
     * que recibe del socket que estamos conectados*/
    int recibir(char *buffer, size_t largo);
    /*Realiza el shutdown del socket*/
    void shutdown();

private:
    /*Metodo privado que realiza la operacion de connect o bind, segun
     * el puntero a funcion que se le pase por parametro*/
    void connect_bind(const char *hostname, const char *port,
                      connect_bind_funcion_t connect_bind_funcion);
};

#endif
