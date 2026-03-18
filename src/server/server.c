#include "server.h"
#include "common.h"


packet_t *to_send = NULL;
size_t to_send_len = 0;
oe_hashmap_t channels = {0};

static void free_elements(char *key, void *val) {
	(void)key;
	free(val);
}

void handle_sigint(int sig) {
	(void)sig;
	oe_hashmap_free(&channels, free_elements);
	free(to_send);
	to_send = NULL;
	to_send_len = 0;
	printf("Au revoir !\n");
}

int main(void) {
	oe_hashmap_init(&channels, 4096);
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
			server_reader(fd);
		if (pfd.revents & POLLOUT && to_send_len)
			server_sender(fd);
	}
	close(fd);
	return 0;
}
