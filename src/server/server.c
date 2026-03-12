#include "server.h"
#include "common.h"
#include <signal.h>
#include <sys/poll.h>

void handle_sigint(int sig) {
	(void)sig;
	printf("\nAu revoir !\n");
}

int main(void) {
	signal(SIGINT, handle_sigint);
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("bind");
		close(fd);
		return 1;
	}
	while (1) {
		struct pollfd pfd;
		pfd.fd = fd;
		pfd.revents = 0;
		pfd.events = POLLIN;
		if (to_send_len)
			pfd.events |= POLLOUT;

		int ret = poll(&pfd, 1, -1);
		if (ret < 0)
			break;

		if (pfd.revents & POLLIN)
			read_client(fd);
		if (pfd.revents & POLLOUT)
			update_send(fd);
		// 	struct sockaddr_in client;
		// 	socklen_t client_len = sizeof(client);

		// 	char buf[MAX_PACKET_LEN];

		// 	int n = recvfrom(fd, buf, MAX_PACKET_LEN, 0, (struct sockaddr *)&client, &client_len);
		// 	packet_t packet = (packet_t){0};

		// 	if (parse_packet(&packet, buf, n))
		// 		continue;

		// 	if (buf[0] == 'R') {

		// 	}
		// 	else if(buf[0] == 'W') {

		// 	}
		// 	else if (buf[0] == 'L') {
		// 		to_send = realloc(to_send, (to_send_len + 1) * sizeof(packet_t));
		// 		to_send[to_send_len - 1].addr = client;
		// 		msg_lst *lst = oe_hashmap_get(&channels, "general");
		// 		sprintf(to_send[to_send_len].buffer, "%lu", lst->len);
		// 		to_send[to_send_len].type = 'l';
		// 		to_send[to_send_len].xid =
		// 		to_send_len++;
		// 	}
		// }
	}
	close(fd);
	return 0;
}
