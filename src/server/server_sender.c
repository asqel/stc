#include "common.h"
#include "server.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

void server_sender(int fd) {
	to_send_len--;
	struct sockaddr_in client_addr = to_send[to_send_len].addr;
	char buf[PACKET_LEN] = {0};
	pack_packet(buf, to_send[to_send_len]);
	sendto(fd, buf, PACKET_LEN, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
	to_send = realloc(to_send, to_send_len * sizeof(packet_t));
	if (!to_send){
		free(to_send);
		return;
	}
}
