#include "common.h"
#include "server.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

void update_send(int fd) {
	to_send_len--;
	struct sockaddr_in client_addr = to_send[to_send_len].addr;
	sendto(fd, (void *)&to_send[to_send_len], sizeof(packet_t), 0, (void *)&client_addr, sizeof(client_addr));
	to_send = realloc(to_send, to_send_len * sizeof(packet_t));
	if (!to_send){
		free(to_send);
		return;
	}
}
