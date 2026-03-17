#include "client.h"
#include "common.h"

void client_write(int fd, packet_t packet) {
	if (sendto(fd, &packet, PACKET_LEN, 0, (void *)&packet.addr, sizeof(packet.addr)) < 0)
		return;
}
