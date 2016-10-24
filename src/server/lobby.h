#ifndef SELFTP_LOBBY_H
#define SELFTP_LOBBY_H

#include "object.h"

class Lobby : public Object{
private:
public:
    Lobby();
    ~Lobby();
    void collect();
};

#endif
