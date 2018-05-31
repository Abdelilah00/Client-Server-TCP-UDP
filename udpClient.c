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
    int client_socket;
    struct sockaddr_in server;
    char message[1024], messag[200];
    socklen_t addr_size;

    //creat socket
    client_socket = socket(PF_INET, SOCK_DGRAM, 0);
    //set server à null
    memset(&server, '\0', sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    //taper un message puis envoyer au server et puis recevoir se message
    printf("Client: \t");
    scanf("%s", &message[0]);
    sendto(client_socket, message, 1024, 0, (struct sockaddr*) &server, sizeof(server));
    recvfrom(client_socket, message, 1024, 0, (struct sockaddr*) &server, &addr_size);
    printf("[+]Data Received: %s\n", message);

}
