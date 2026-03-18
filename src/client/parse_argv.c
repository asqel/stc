#include "client.h"
#include "common.h"
#include <string.h>

#define MAX(X, Y) (X > Y ? X : Y)
/*
./stc -> read
./stc msg ->send
./stc [-n] [-channel] msg -> send
./stc -channel -> red
 */
void parse_argv(packet_t *packet, int argc, char **argv) {
	int has_n = 1;
	strcpy(packet->channel, "general");
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], "-n")) {
				has_n = !has_n;
			}
			else {
				memset(packet->channel, 0, CHANNEL_LEN);
				if (strlen(argv[i]) > CHANNEL_LEN) {
					perror("channel to long");
					return;
				}
				strcpy(packet->channel, argv[i]);
			}
		}
		else {
			memset(packet->data, 0, MESSAGE_LEN);
			if (strlen(argv[i]) + has_n > MESSAGE_LEN) {
				perror("message to long");
				return;
			}

			if (has_n)
				sprintf(packet->data, "%s%c", argv[i], '\n');
			else
				strcpy(packet->data, argv[i]);
		}
	}
	packet->type = 'R';
	if (strlen(packet->data)) {
		packet->type = 'W';
	}
}
