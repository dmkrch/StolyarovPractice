#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define SERVERPORT 5000
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1
#define MAX_STRING_SIZE 50


typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char* msg);
char* GetCurrentTime();

int main(int argc, char **argv)
{
    int client_socket;               
    SA_IN server_addr;

    if(argc != 2)
    {
        printf("\n Usage: %s <file name> \n",argv[0]);
        return 1;
    }

    /* now we create socket for client to connect to server afterwards */
    check((client_socket = socket(AF_INET, SOCK_STREAM, 0)),
        "Failed to create socket");

    server_addr.sin_family = AF_INET;         // setting type of family to struct
    server_addr.sin_port = htons(SERVERPORT);       // setting port number to struct

    /* setting ip address of server to struct */
    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    /* now we can throw request of connecting to our server */
    check(connect(client_socket, (SA*)&server_addr, sizeof(server_addr)), 
        "Connect failed");
        
    char serverMessage[MAX_STRING_SIZE];
    char buffer[BUFSIZE];

    char name[MAX_STRING_SIZE];
    fprintf(stdout, "Enter your name: ");
    fgets(name, sizeof(name), stdin);
    size_t ln = strlen(name)-1;
    if(name[ln] == '\n')
        name[ln] = '\0';

    char* currentTime;


    switch(fork())
    {
        case -1:
            perror("fork");
            break;
        case 0:     // child process - will accept messages and print
            while(true)
            {
                /* getting message from client */
                recv(client_socket, buffer, sizeof(buffer), 0);

                fprintf(stdout, "%s", buffer);
            }
        // parent process - sends messages to clients
        default:    
            while(true)
            {
                currentTime = GetCurrentTime();

                /* getting message from stdint */
                fgets(serverMessage, sizeof(serverMessage), stdin);

                snprintf(buffer, sizeof(buffer), "\t\t\t%s %s - %s", currentTime, name, serverMessage);

                /* now we need to move this string to buffer, so that server get it */
                send(client_socket, buffer, sizeof(buffer), 0);
            }
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

char* GetCurrentTime()
{
    struct tm* u;
    const time_t timer = time(NULL);
    u = localtime(&timer);
    char s[40];
    char *tmp;
    for (int i = 0; i<40; i++) s[i] = 0;
    strftime(s, 40, "%d.%m.%Y %H:%M:%S", u);
    tmp = new char[sizeof(s)];
    strcpy(tmp, s);

    return tmp;
}