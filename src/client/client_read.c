#include "client.h"

void client_read(int fd, sockaddr_in addr) {
	packet_t packet = (packet_t){0};
	packet.addr = addr;
	packet.type = 'R';
	strcpy(packet.channel, "general");
	strcpy(packet.data, argv[2]);
	sendto(fd, &packet, PACKET_LEN, 0, (void *)&addr, sizeof(addr));

	poll(struct pollfd *fds, nfds_t nfds, int timeout)
}
