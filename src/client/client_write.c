#include "client.h"
#include "common.h"
#include <string.h>

void client_write(int fd, packet_t packet) {
	char buf[PACKET_LEN] = {0};
	pack_packet(buf, packet);
	if (sendto(fd, &buf, PACKET_LEN, 0, (void *)&packet.addr, sizeof(packet.addr)) < 0) {
		perror("send error");
		return;
	}
}
