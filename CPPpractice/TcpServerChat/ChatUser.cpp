#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <netinet/in.h>

#define SERVERPORT 8989
#define IP_ADDRESS "127.0.0.1"
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char* msg);

int main(int argc, char **argv)
{
    int client_socket;               
    SA_IN server_addr;
    char recvBuffer[BUFSIZE];

    /* now we create socket for client to connect to server afterwards */
    check((client_socket = socket(AF_INET, SOCK_STREAM, 0)),
        "Failed to create socket");

    server_addr.sin_family = AF_INET;         // setting type of family to struct
    server_addr.sin_port = htons(8989);       // setting port number to struct

    /* setting ip address of server to struct */
    if(inet_pton(AF_INET, IP_ADDRESS, &server_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    /* now we can throw request of connecting to our server */
    check(connect(client_socket, (SA*)&server_addr, sizeof(server_addr)), 
        "Connect failed");


    while(1)
    {
        /* now we need to move this string to buffer, so that server get it 
        send(client_socket, argv[1], 100, 0); */

        /* getting data from server */

        int bytes_read = recv(client_socket, recvBuffer, BUFSIZE, 0);
        printf("%d\n", bytes_read);

        recvBuffer[bytes_read] = '\0';

        /* printing this data to stdout */
        printf("%s", recvBuffer);

        /* clearing buffer */
        memset(recvBuffer, '0', BUFSIZE);
    }

    close(client_socket);

    return 0;
}


int check(int exp, const char* msg)
{
    if (exp == SOCKETERROR)
    {
        perror(msg);
        exit(1);
    }

    return exp; 
}