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

#define PORT 42124
#define TYPE_LEN 1
#define CHANNEL_LEN 16
#define MESSAGE_LEN 1000
#define PACKET_LEN  (TYPE_LEN + CHANNEL_LEN + MESSAGE_LEN)

typedef struct {
	struct sockaddr_in addr;
	uint8_t type;
	char channel[CHANNEL_LEN + 1];
	char data[MESSAGE_LEN + 1];
} packet_t;

void pack_packet(char *buf, packet_t packet);
int unpack_packet(packet_t *packet, char *buffer, int len);

void print_packet(packet_t packet);

#endif
