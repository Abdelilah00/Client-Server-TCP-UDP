#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(int argc, char **argv){
    // test si les parametres est < 3 exit
    if(argc != 3){
        printf("Usage: %s <IP>\t<port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[2]);
    int server_socket;
    struct sockaddr_in server, other_client;
    char message[1024];
    socklen_t addr_size;

    //creat socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    // server = null
    memset(&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(argv[1]);
    //bind the socket
    bind(server_socket, (struct sockaddr*)&server, sizeof(server));
    addr_size = sizeof(other_client);
    //si le message est != exit la socket rest en mode listen
    while(1){
        recvfrom(server_socket, message, 1024, 0, (struct sockaddr*)& other_client, &addr_size);
        sendto(server_socket, message, 1024, 0, (struct sockaddr*)& other_client, sizeof(server));
        if(strcmp(message,"exit")==0){
            printf("exit ligne");
            exit(1);
        }else
        printf("[+]Data Received: %s\n", message);
        bzero(message, sizeof(message));
    }


}
