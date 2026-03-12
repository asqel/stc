#include "server.h"
#include <string.h>

int parse_packet(packet_t *packet, char *buffer, int len) {
	if (len < MAX_PACKET_LEN)
		return 1;
	packet->type = buffer[0];
	packet->xid = buffer[1];
	memcpy(packet->channel, &buffer[2], 16);
	memcpy(packet->data, &buffer[18], MAX_PACKET_LEN - 18);
	return 0;
}
