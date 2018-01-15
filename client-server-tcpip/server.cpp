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
	if(argc < 2)
	{
		printf("Usage: %s <portno>", argv[0]);
		return 0;
	}

	struct sockaddr_in server, client;

	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sfd < 0) end("ERROR: socket file descriptor.");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = atoi(argv[1]);

	if(bind(sfd, (struct sockaddr *)&server, sizeof(server)))
		end("ERROR: bind");

	listen(sfd, 5);
	
	printf("Listening on port: %s", argv[1]);
	
	long clientLength = sizeof(client);
	int clientfd = accept(sfd, (struct sockaddr *)&client, (socklen_t *)&clientLength);
	if(clientfd < 0) end("ERROR: accept");

	char *message = "Hello from server";
	int n = write(clientfd, message, strlen(message));
	
}	
