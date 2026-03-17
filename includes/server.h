#ifndef SERVER_H
#define SERVER_H

#include "common.h"

#define DELETE_TIME 5

extern packet_t *to_send;
extern size_t to_send_len;

extern oe_hashmap_t channels;

char	*itoa(int n);

void read_client(int fd);

void write_channel(char channel[CHANNEL_LEN + 1], char data[MESSAGE_LEN + 1]);
void read_channel(packet_t packet);

void update_send(int fd);

#endif
