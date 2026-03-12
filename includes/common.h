#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <oeuf.h>

#define PORT 8080
#define MAX_PACKET_LEN  1024

typedef struct {
	struct sockaddr_in addr;
	uint8_t type;
	uint8_t xid;
	char channel[17];
	char data[MAX_PACKET_LEN];
} packet_t;

int parse_packet(packet_t *packet, char *buffer, int len);

#endif
