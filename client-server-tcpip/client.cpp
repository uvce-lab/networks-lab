#define BUF (4096)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

#include <iostream>
#include <string>
using namespace std;

void end(char *message)
{
	perror(message);
	exit(0);
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		printf("Usage: %s <server-ip> <port> <fileName>\n", argv[0]);
		return 0;
	}

	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		end("ERROR: could not create socket.\n");

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		end("ERROR: could not connect to the server.\n");
	else
		printf("Connected to server at %s:%s\n", argv[1], argv[2]);

	write(sock, argv[3], strlen(argv[3]));

	char buffer[BUF];
	strcpy(buffer, "");
	int n = read(sock, buffer, BUF - 1);

	if (n < 0)
		end("ERROR: reading on socket.\n");

	printf("Received data: \n%s\n", buffer);

	close(sock);
}
