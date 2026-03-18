#include "client.h"
#include "common.h"

int main(int argc, char **argv)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;        // IPv4
	struct hostent *info = gethostbyname(SERVER_ADDR);
    if (!info) {
    perror("host not found");
        return -1;
    }
    memcpy(&addr.sin_addr, info->h_addr_list[0], 4);
	addr.sin_port = htons(PORT);

	packet_t packet = (packet_t){0};
	packet.addr = addr;
	parse_argv(&packet, argc, argv);

	if (packet.type == 'R') {
		client_read(fd, packet);
	}
	else if (packet.type == 'W') {
		client_write(fd, packet);
	}
	close(fd);
	return (0);
}
