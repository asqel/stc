#ifndef CLIENT_H
#define CLIENT_H

#include <netdb.h>
#include "common.h"

#define SERVER_ADDR "127.0.0.1"

void parse_argv(packet_t *packet, int argc, char **argv);
void client_read(int fd, packet_t packet);
void client_write(int fd, packet_t packet);

#endif
