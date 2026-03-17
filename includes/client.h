#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

#define SERVER_ADDR "127.0.0.1"

void client_read(int fd, sockaddr_in addr);

#endif
