#include "client.h"
#include "common.h"
#include <stdio.h>
#define TRY 5

void client_read(int fd, packet_t packet) {
	char buf[PACKET_LEN] = {0};
	pack_packet(buf, packet);
	for (int i = 0; i < TRY; i++) {
		if (sendto(fd, &buf, PACKET_LEN, 0, (void *)&packet.addr, sizeof(packet.addr)) < 0) {
			perror("send error");
			return;
		}
		struct pollfd pfd;
		pfd.fd = fd;
		pfd.revents = 0;
		pfd.events = POLLIN;
		poll(&pfd, 1, 500);
		if (pfd.revents & POLLIN) {
			int n = recv(fd, buf, PACKET_LEN, 0);
			unpack_packet(&packet, buf, n);
			printf("%s\n", packet.data);
			break;
		}
	}
}
