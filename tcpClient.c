#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv){

	if(argc != 3){
		printf("Usage: %s <IP>\t<port>\n", argv[0]);
		exit(0);
	}

	int port = atoi(argv[2]), socket_client, conct;
    struct sockaddr_in serverAddr;
	char message[1024];

	socket_client = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_client < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	conct = connect(socket_client, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(conct < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		printf("Client: \t");
		scanf("%s", &message[0]);
		send(socket_client, message, strlen(message), 0);

		if(strcmp(message, ":exit") == 0){
			close(socket_client);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(socket_client, message, 1024, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", message);
		}
	}

	return 0;
}