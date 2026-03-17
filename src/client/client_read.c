#include "client.h"
#include "common.h"

void client_read(int fd, packet_t packet) {
	char buf[PACKET_LEN] = {0};
	pack_packet(buf, packet);
	if (sendto(fd, &buf, PACKET_LEN, 0, (void *)&packet.addr, sizeof(packet.addr)) < 0) {
		perror("send error");
		return;
	}

	struct pollfd pfd;
	pfd.fd = fd;
	pfd.revents = 0;
	pfd.events = POLLIN;
	poll(&pfd, 1, -1);
	if (pfd.revents & POLLIN) {
		int n = recv(fd, buf, PACKET_LEN, 0);
		unpack_packet(&packet, buf, n);
		print_packet(packet);
	}
}
