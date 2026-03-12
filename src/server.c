#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>

#define PORT 8080

typedef struct message_t {
	int time;
	char *message;
}message_t;

message_t *messages;
int count = 0;

void handle_sigint(int sig)
{
	(void)sig;
	printf("\nAu revoir !\n");
	for (int i = 0; i < count; i++) {
		free(messages[i].message);
	}
	free(messages);
	exit(0);
}

int main(void)
{
	signal(SIGINT, handle_sigint);  // Ctrl+C
	signal(SIGTERM, handle_sigint); // kill (terminaison propre)
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port        = htons(PORT)
	};

	bind(fd, (struct sockaddr *)&addr, sizeof(addr));

	struct pollfd pfd = {
		.fd		= fd,
		.events	= POLLIN
	};

	char buf[1024];

	while (1) {
		int ret = poll(&pfd, 1, 1000);
		if (ret < 0)
			break;
		if (ret == 0) {
			continue;
		}
		if (ret > 0) {
			struct sockaddr_in client;
			socklen_t client_len = sizeof(client);

			ssize_t n = recvfrom(fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&client, &client_len);
			buf[n] = '\0';
			if (buf[0] == 'r') {
				for (int i = 0; i < count; i++) {
					printf("%s\n", messages[i].message);
					sendto(fd, messages[i].message, strlen(messages[i].message), 0, (struct sockaddr *)&client, client_len);
				}
				sendto(fd, "end", 3, 0, (struct sockaddr *)&client, client_len);
			}
			else if(buf[0] == 'w') {
				count++;
				messages = realloc(messages, count * sizeof(message_t));
				messages[count - 1].message = strdup(&buf[1]);
				messages[count - 1].time = 5;
				printf("message added\n");
			}
		}
	}
	for (int i = 0; i < count; i++) {
		free(messages[i].message);
	}
	free(messages);
	close(fd);
	return 0;
}
