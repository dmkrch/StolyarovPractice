#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define BUFFSIZE 1025

int main(int argc, char** argv)
{
    int listenfd = 0;           // contains listen descriptor of server
    int connfd = 0;             // contains connection descriptor of server
    struct sockaddr_in serv_addr;   // contains address of server socket

    /* buffer for data */
    char sendBuff[BUFFSIZE];
    const char* helloMessage = "Hello from server!\n";

    /* creating a new socket for listening in server */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    /* initializing sockaddr_in and buffer with zeros */
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));


    /* initializing container for address of server socket */
    serv_addr.sin_family = AF_INET;       // setting type of socket family
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // setting random free ip
    serv_addr.sin_port = htons(5000);       // setting port 5000


    /* actually our socket has its own address. Now we need to bind it with
       free file descriptor. That file descriptor (listenfd) will point to
       our socket */
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);  // we transform socket into listening mode


    while(1)
    {
        /* connfd is file descriptor of interraction-socket(connection socket)
           of server and client */
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        /* write formatted string to buffer */
        snprintf(sendBuff, sizeof(sendBuff), "%s\r\n", helloMessage);

        /* writing buffer data to connection-socket */
        write(connfd, sendBuff, strlen(sendBuff));

        /* closing connection-socket */
        close(connfd);
        sleep(1);
    }
}
