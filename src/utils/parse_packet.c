#include "server.h"
#include <string.h>

int parse_packet(packet_t *packet, char *buffer, int len) {
	if (len != PACKET_LEN)
		return 1;
	packet->type = buffer[0];
	memcpy(packet->channel, &buffer[TYPE_LEN], CHANNEL_LEN);
	packet->channel[CHANNEL_LEN] = '\0';
	memcpy(packet->data, &buffer[TYPE_LEN + CHANNEL_LEN], MESSAGE_LEN);
	packet->data[MESSAGE_LEN] = '\0';
	return 0;
}
