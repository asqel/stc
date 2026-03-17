#include "client.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

void parse_argv(packet_t *packet, int argc, char **argv) {
	if (!strcmp(argv[1], "r") || !strcmp(argv[1], "read"))
		packet->type = 'R';
	else if (!strcmp(argv[1], "w") || !strcmp(argv[1], "write"))
		packet->type = 'W';

	if (packet->type == 'R') {
		if (argc == 3)
			strcpy(packet->channel, argv[2]);
		else
			strcpy(packet->channel, "general");
	}
	if (packet->type == 'W') {
		if (argc == 4) {
			strlcpy(packet->channel, argv[2], CHANNEL_LEN);
			strcpy(packet->data, argv[3]);
		}
		else {
			strcpy(packet->channel, "general");
			strcpy(packet->data, argv[2]);
		}
	}
}
