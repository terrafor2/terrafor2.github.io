#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t adr_sz;

	struct sockaddr_in serv_adr, from_adr;
	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\m", argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
	{
		error-handling("socket{} error");
	}

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	while(1)
	{
		fputs("Insert message(q to quit): ", stdout);
		fgets(message, sizeof(message),stdin);
		if(!strcmp(message, "q\n" || !strcmp(message,"Q\n"))
	}
}
