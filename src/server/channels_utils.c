#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_channel(char channel[CHANNEL_LEN + 1], char data[MESSAGE_LEN + 1]) {
	char *message = oe_hashmap_get(&channels, channel);
	if (!message) {
		message = calloc(MESSAGE_LEN + 1, 1);
		oe_hashmap_set(&channels, channel, message);
	}
	int data_len = strlen(data);
	int msg_len = strlen(message);

	if (msg_len + data_len > MESSAGE_LEN) {
		int rest = MESSAGE_LEN - data_len;
		memmove(message, &message[msg_len - rest], rest + 1);
		msg_len = rest;
	}
	strcpy(&message[msg_len], data);
	//printf("data: %s, channel: %s\n", data, message);
}

void read_channel(packet_t packet) {
	memset(packet.data, 0, MESSAGE_LEN);
	char *message = oe_hashmap_get(&channels, packet.channel);
	if (message)
		memcpy(packet.data, message, MESSAGE_LEN);

	to_send_len++;
	to_send = realloc(to_send, to_send_len * sizeof(packet_t));
	if (!to_send){
		free(to_send);
		return;
	}
	to_send[to_send_len - 1] = packet;
}
