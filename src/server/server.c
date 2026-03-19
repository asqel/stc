#include "server.h"
#include <time.h>
#include "common.h"

packet_t *to_send = NULL;
size_t to_send_len = 0;
oe_hashmap_t channels = {0};

static int has_alarmed = 0;
static int fd = -1;

static void free_elements(char *key, void *val) {
	(void)key;
	free(val);
}


int get_next_alarm() {
	time_t now = time(NULL);
	struct tm *tm_struct = localtime(&now);
	char buffer[256] = {0};
	strftime(buffer, 255, "%H", tm_struct);
	int hour = atoi(buffer);
	int res = 0;
	if (hour < 4)
		res = (4 - hour) * 3600;
	else
		res = (24 - hour + 4) * 3600;
	printf("next alarm in %ds / %dh\n", res, res / 3600);
	return res;
}

static void do_alarm(void) {
	has_alarmed = 0;
	char **keys = oe_hashmap_get_keys(&channels);
	for (size_t i = 0; keys[i]; i++) {
		if (!keys[i][0])
			continue;
		oe_hashmap_remove(&channels, keys[i], free_elements);
	}
	oe_hashmap_free_keys(keys);
	alarm(get_next_alarm());
}

void handle_sigint(int sig) {
	if (sig == SIGALRM)
		has_alarmed = 1;
	else if (sig == SIGINT) {
		oe_hashmap_free(&channels, free_elements);
		free(to_send);
		to_send = NULL;
		to_send_len = 0;
		printf("\nAu revoir !\n");
		if (fd >= 0)
			close(fd);
		fd = -1;
		exit(0);
	}
}

int main(void) {
	oe_hashmap_init(&channels, 4096);
	oe_hashmap_set(&channels, "", calloc(MESSAGE_LEN + 1, 1));
	signal(SIGINT, handle_sigint);
	signal(SIGALRM, handle_sigint);
	fd = socket(AF_INET, SOCK_DGRAM, 0);
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
	alarm(get_next_alarm());
	while (1) {
		struct pollfd pfd;
		pfd.fd = fd;
		pfd.revents = 0;
		pfd.events = POLLIN;
		if (to_send_len)
			pfd.events |= POLLOUT;

		poll(&pfd, 1, -1);

		if (pfd.revents & POLLIN)
			server_reader(fd);
		if (pfd.revents & POLLOUT && to_send_len)
			server_sender(fd);

		if (has_alarmed) {
			do_alarm();
		}
	}
	close(fd);
	return 0;
}
