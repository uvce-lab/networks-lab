#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void end(char *message)
{
	perror(message);
	exit(0);
}

int main(int argc, char** argv)
{
	if(argc < 3) 
	{
		printf("Usage: %s <server-hostname> <port>", argv[0]);
		return 0;
	}
	
	struct sockaddr_in server;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = atoi(argv[2]);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) end("ERROR: could not create socket.");

	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
		end("ERROR: could not connect to the server.");
	
	printf("Connected to server at %s:%s.", argv[1], argv[2]);

	char buffer[100];
	int n = read(sock, buffer, 100);
	
	if(n < 0) end("ERROR: reading on socket.");
	
	printf("Message from server: %s", buffer); 			
}
