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
	int port = atoi(argv[2]);
    int i=0;
    int socket_server, newSocket, ret;
	struct sockaddr_in newAddr,serverAddr;
	socklen_t addr_size;

	char message[1024];
	pid_t childpid;

	socket_server = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_server < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	ret = bind(socket_server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(socket_server, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(socket_server, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(socket_server);
			while(1){
				recv(newSocket, message, 1024, 0);
				if(strcmp(message, ":exit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					printf("Client: %s\n", message);
					send(newSocket, message, strlen(message), 0);
					bzero(message, sizeof(message));
                    if(i++>100000)exit(1);
				}
			}
		}

	}
	close(newSocket);
	return 0;
}