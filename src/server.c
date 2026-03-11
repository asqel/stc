#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>

#define PORT 8080

typedef struct message_t {
	int time;
	char *sender;
	char *message;
}message_t;

message_t *messages;
int count = 0;

int main(void)
{
	// ── 1. CRÉATION DU SOCKET ──────────────────────────────────────────
	// AF_INET      = IPv4
	// SOCK_DGRAM   = UDP (pas de connexion, paquets indépendants)
	// 0            = protocole par défaut (UDP pour DGRAM)
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	// ── 2. ADRESSE DU SERVEUR ──────────────────────────────────────────
	// On décrit sur quelle IP/port le serveur va écouter
	struct sockaddr_in addr = {
		.sin_family = AF_INET,        // IPv4
		.sin_addr.s_addr = INADDR_ANY,     // accepte toutes les interfaces (0.0.0.0)
		.sin_port        = htons(PORT)     // htons = host to network short (endianness)
	};

	// ── 3. BIND ────────────────────────────────────────────────────────
	// Attache le socket à l'adresse/port décrit au-dessus
	// Sans bind, le kernel choisit un port aléatoire → le client ne saurait pas où écrire
	bind(fd, (struct sockaddr *)&addr, sizeof(addr));

	// ── 4. POLL ────────────────────────────────────────────────────────
	// poll() surveille un ou plusieurs fd en même temps
	// Ici on surveille fd, en attente de données lisibles (POLLIN)
	struct pollfd pfd = {
		.fd		= fd,
		.events	= POLLIN   // on veut être notifié quand des données arrivent
	};

	char buf[1024];

	while (1) {
		// poll() bloque jusqu'à ce qu'un événement arrive (ou timeout si > 0)
		// -1 = timeout infini
		// retourne le nombre de fd prêts, 0 si timeout, -1 si erreur
		int ret = poll(&pfd, 1, 1000);
		if (ret < 0)
			break;
		if (ret == 0) {
			continue;
		}
		if (ret > 0) {
			// ── 5. RECVFROM ───────────────────────────────────────────────
			// Comme read() mais remplit aussi 'client' avec l'adresse de l'expéditeur
			// Indispensable en UDP : pas de connexion → on ne sait pas qui a envoyé
			struct sockaddr_in client;
			socklen_t client_len = sizeof(client);

			ssize_t n = recvfrom(fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&client, &client_len);
			buf[n] = '\0';
			if (buf[0] == 'r') {
				char *reply = "Hello from server";
				sendto(fd, reply, strlen(reply), 0, (struct sockaddr *)&client, client_len);
			}
			else if(buf[0] == 'w') {
				count++;
				messages = realloc(messages, count);
				messages[count - 1].message = buf;
				messages[count - 1].sender = "jean";
				messages[count - 1].time = 5;
				printf("message added\n");
			}
			// ── 6. SENDTO ─────────────────────────────────────────────────
			// Comme write() mais on précise la destination
			// On réutilise 'client' récupéré dans recvfrom → on répond à l'expéditeur
		}
	}

	close(fd);
	return 0;
}
