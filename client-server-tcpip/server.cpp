#define BUF (4096)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

void end(char *message)
{
	perror(message);
	exit(0);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("\nUsage: %s <portno>", argv[0]);
		return 0;
	}

	struct sockaddr_in server;

	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sfd < 0)
		end("ERROR: socket file descriptor.");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));

	if (bind(sfd, (struct sockaddr *)&server, sizeof(server)))
		end("ERROR: bind");

	listen(sfd, 5);

	printf("Listening on port: %s\n", argv[1]);

	char buffer[BUF], filePath[100];
	while (1)
	{
		struct sockaddr_in client;
		int clientLength = sizeof(client);
		int clientfd = accept(sfd, (struct sockaddr *)&client, (socklen_t *)&clientLength);
		if (clientfd < 0)
			end("ERROR: accept");

		strcpy(filePath, "");
		strcpy(buffer, "");

		int n = read(clientfd, filePath, 100);
		if (n < 0)
			end("ERROR: unable to read from socket");
		else
			printf("Serve: %s\n", filePath);

		FILE *file = fopen(filePath, "r");
		if (file != NULL)
		{
			int i = 0;
			char ch = fgetc(file);
			while (ch != EOF && i < 4096)
			{
				buffer[i++] = ch;
				ch = fgetc(file);
			}
			buffer[i] = 0;
			write(clientfd, buffer, strlen(buffer));
		}
		else
		{
			write(clientfd, "File not found.", 16);
		}

		close(clientfd);
	}
}