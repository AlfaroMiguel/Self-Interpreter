#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <typeinfo>

#define SOCKET_ERROR_LEN_BUFFER 256
/*Excepcion que representa algun error del socket
 * tiene un mensaje informativo acerca de lo que fallo*/
class SocketError : std::exception {
private:
    char mensaje_error[SOCKET_ERROR_LEN_BUFFER];

public:
    /*Constructor de SocketError*/
    SocketError() noexcept;
    /*Constructor que recibe un mensaje informativo del error*/
    explicit SocketError(char *str_error) noexcept;
    /*Metodo que devuelve el mensaje informativo del error*/
    virtual const char *what() const noexcept;
    /*Destructor de SocketError*/
    virtual ~SocketError() noexcept;
};

#endif
