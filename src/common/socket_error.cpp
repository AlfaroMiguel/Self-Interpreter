#include "socket_error.h"

#include "errno.h"

SocketError::SocketError() throw() {
    int _errno = errno;
    char buffer[SOCKET_ERROR_LEN_BUFFER];
    const char *_m = strerror_r(_errno, buffer, SOCKET_ERROR_LEN_BUFFER);
    strncpy(mensaje_error, _m, SOCKET_ERROR_LEN_BUFFER);
    mensaje_error[SOCKET_ERROR_LEN_BUFFER - 1] = 0;
}

SocketError::SocketError(char *str_error) noexcept {
    strncpy(mensaje_error, str_error, SOCKET_ERROR_LEN_BUFFER);
}

const char *SocketError::what() const noexcept {
    return mensaje_error;
}

SocketError::~SocketError() {}
