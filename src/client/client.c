#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "client.h"
#include "common.h"

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;

	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;        // IPv4
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);    // converti l'ip en binaire
	addr.sin_port = htons(PORT);

	packet_t packet = (packet_t){0};
	parse_argv(&packet, argc, argv);

	if (packet.type == 'r') {
		client_read(fd, packet);
	}
	else if (packet.type == 'w') {
		client_write(fd, packet);
	}
	close(fd);
	return (0);
}
