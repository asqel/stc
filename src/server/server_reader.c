#include "common.h"
#include "server.h"
#include <sys/socket.h>
#include <uchar.h>

void server_reader(int fd) {
	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	char buf[PACKET_LEN];
	int n = recvfrom(fd, buf, PACKET_LEN, 0, (struct sockaddr *)&client, &client_len);

	packet_t packet = (packet_t){0};
	packet.addr = client;
	if (unpack_packet(&packet, buf, n))
		return;
	if (packet.type == 'W')
		write_channel(packet.channel, packet.data);
	else if (packet.type == 'R')
		read_channel(packet);
}
