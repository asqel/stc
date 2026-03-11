#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,        // IPv4
        .sin_addr.s_addr = 0,
        .sin_port        = 0    // htons = host to network short (endianness)
    };
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);    // converti l'ip en binaire
    addr.sin_port = htons(PORT);

    if (strcmp(argv[1], "r") == 0) {
    	sendto(fd, "r", 1, 0, (struct sockaddr *) &addr, sizeof(addr));
     	struct pollfd pfd = {
         	.fd      = fd,
         	.events  = POLLIN   // on veut être notifié quand des données arrivent
      };

     	int ret = poll(&pfd, 1, -1);
     	if (ret < 0) {
         	return (1);
     	}

     	struct sockaddr_in server;
     	socklen_t server_len = sizeof(server);
     	char buf[1024];
     	ssize_t n = recvfrom(fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *) &server, &server_len);
     	buf[n] = '\0';
     	printf("Reçu : %s\n", buf);
    }
    else if (strcmp(argv[1], "w") == 0) {
    	char *message = strcat("w", argv[2]);
    	sendto(fd, message, strlen(message), 0, (struct sockaddr *) &addr, sizeof(addr));
    }
    return (0);
}
