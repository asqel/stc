#include "common.h"

void print_packet(packet_t packet) {
	printf("type: %c, channel: %s, message: %s\n", packet.type, packet.channel, packet.data);
}
