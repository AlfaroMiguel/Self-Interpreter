#include "socket.h"
#include <string>

#define SOCKET_EXITO 0
#define SOCKET_ERROR -1
#define FD_INVALIDO -1
#define CANT_CLIENTES 10

/*Recibe una cadena con el hostname y un puerto.
Y ademas una funcion que puede ser connect o bind ya que tienen la misma firma
Devuelve como resultado si puedo hacer cualquiera de las dos cosas*/
void Socket::connect_bind(const char *hostname, const char *port,
                          connect_bind_funcion_t connect_bind_funcion) {
    int s = 0;
    struct addrinfo hints, *resultado, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    s = getaddrinfo(hostname, port, &hints, &resultado);
    if (s != SOCKET_EXITO) throw SocketError();
    for (ptr = resultado; ptr != NULL; ptr = ptr->ai_next) {
        int s = connect_bind_funcion(this->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (s != SOCKET_ERROR)break;
    }
    freeaddrinfo(resultado);
    if (!ptr)throw SocketError(); //No quedan direcciones validas
    // y no se pudo conectar o bindear
}

Socket::Socket() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd == SOCKET_ERROR)
        throw SocketError();
}

Socket::~Socket() {
    if (fd != FD_INVALIDO) {
        shutdown();
        close(fd);
    }
}

Socket::Socket(Socket &&otro) : fd((otro.fd)) {
    otro.fd = FD_INVALIDO;
}

Socket &Socket::operator=(Socket &&otro) {
    this->fd = otro.fd;
    otro.fd = FD_INVALIDO;
    return *this;
}

void Socket::bind_and_listen(std::string &puerto) {
    connect_bind(NULL, puerto.c_str(), bind);
    listen(fd, CANT_CLIENTES);
}

void Socket::conectar(std::string &hostname, std::string &puerto) {
    return connect_bind(hostname.c_str(), puerto.c_str(), connect);
}

void Socket::aceptar(Socket &socket_aceptado) {
    int accepted_skt = accept(this->fd, NULL, NULL);
    if (accepted_skt == SOCKET_ERROR)throw SocketError();
    if (socket_aceptado.fd != FD_INVALIDO){
        ::shutdown(socket_aceptado.fd, SHUT_RDWR);
        close(socket_aceptado.fd);
    }
    socket_aceptado.fd = accepted_skt;
}

int Socket::enviar(char *buffer, size_t largo) {
    unsigned int bytes_enviados = 0;
    bool skt_valido = true;
    while (largo > bytes_enviados && skt_valido) {
        ssize_t s = send(fd, &buffer[bytes_enviados], largo - bytes_enviados,
                         MSG_NOSIGNAL);
        if (s < 0) skt_valido = false; //Error inesperado
        else if (s == 0) skt_valido = false; //Nos cerraron el socket
        else
            bytes_enviados += s; //Enviamos bien
    }
    if (!skt_valido)throw SocketError();
    return bytes_enviados;
}

int Socket::recibir(char *buffer, size_t largo) {
    unsigned int bytes_recibidos = 0;
    bool skt_valido = true;
    bool skt_abierto = true;
    while (largo > bytes_recibidos && skt_valido && skt_abierto) {
        ssize_t s = recv(fd, &buffer[bytes_recibidos], largo - bytes_recibidos,
                         MSG_NOSIGNAL);
        if (s < 0) skt_valido = false; //Error inesperado
        else if (s == 0) skt_abierto = false; //Nos cerraron el socket
        else
            bytes_recibidos += s; //Recibimos bien
    }
    if (!skt_valido)throw SocketError();
    return bytes_recibidos;
}

void Socket::shutdown() {
    ::shutdown(fd, SHUT_RDWR);
}
