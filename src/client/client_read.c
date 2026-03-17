#include "client.h"
#include "common.h"

void client_read(int fd, packet_t packet) {
	if (sendto(fd, &packet, PACKET_LEN, 0, (void *)&packet.addr, sizeof(packet.addr)) < 0)
		return;

	struct pollfd pfd;
	pfd.fd = fd;
	pfd.revents = 0;
	pfd.events = POLLIN;
	poll(&pfd, 1, -1);
	if (pfd.revents & POLLIN) {
		char buf[PACKET_LEN];
		recv(fd, buf, PACKET_LEN, 0);
		printf("%s", buf);
	}
}
