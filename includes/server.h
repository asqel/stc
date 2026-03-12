#ifndef SERVER_H
#define SERVER_H

#include "common.h"

typedef struct message_t {
	int64_t time;
	char *message;
} message_t;

typedef struct {
	size_t len;
	message_t *lst;
} msg_lst;


packet_t *to_send = NULL;
size_t to_send_len = 0;

oe_hashmap_t channels = {0};

char	*itoa(int n);

#endif
