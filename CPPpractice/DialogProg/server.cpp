#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>


#define SERVERPORT 5000
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1
#define MAX_STRING_SIZE 100


typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int check(int exp, const char* msg);
char* GetCurrentTime();

int main(int argc, char** argv)
{
    int server_socket;
    int client_socket;
    int addr_size;
 
    SA_IN server_addr;
    SA_IN client_addr;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)),
             "Failed to create socket");

    // initialize the address struct 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    check(bind(server_socket, (SA*)&server_addr,sizeof(server_addr)), 
        "Bind failed!");
    
    check(listen(server_socket, SERVER_BACKLOG),
        "Listen failded!");

    check(client_socket = 
        accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size),
        "Accept failed");

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
        // parent process - sends message to client
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