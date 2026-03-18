#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

#define SERVER_ADDR "asqel.ddns.net"

void parse_argv(packet_t *packet, int argc, char **argv);

void client_read(int fd, packet_t packet);
void client_write(int fd, packet_t packet);

#endif
