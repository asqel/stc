#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <type_traits>
#include <unistd.h>
#include "client.h"

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;

	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;        // IPv4
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);    // converti l'ip en binaire
	addr.sin_port = htons(PORT);


	if (strcmp(argv[1], "r") == 0) {
		client_read(fd, addr);
	}
	else if (strcmp(argv[1], "w") == 0) {
		char *tmp;
		if (argc < 3) {
			char buf[1024];
			int len = read(1, buf, 1024);
			buf[len] = '\0';
			tmp = malloc(len * sizeof(char) + 2);
			sprintf(tmp, "w%s", buf);
		}
		else {
			tmp = malloc(strlen(argv[2]) * sizeof(char) + 2);
			sprintf(tmp, "w%s", argv[2]);
		}
		sendto(fd, tmp, strlen(tmp), 0, (struct sockaddr *) &addr, sizeof(addr));
		printf("sending: %s\n", &tmp[1]);
		free(tmp);
	}
	close(fd);
	return (0);
}
