#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX_STRING_SIZE 25


int main(int argc, char **argv)
{
    int sockfd = 0;      // file descriptor of socket in client
    struct sockaddr_in serv_addr;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // setting zeros to serv addr


    /* now we create socket for client */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;         // setting type of family to struct
    serv_addr.sin_port = htons(5000);       // setting port number to struct

    /* setting ip address from arguments of command line to struct */
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }


    /* now we can throw request of connecting to our server */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }


    while(1)
    {
        fprintf(stdout, "Enter your name: ");
        char name[MAX_STRING_SIZE];
        fgets(name, sizeof(name), stdin);

        /* now we need to move this string to buffer, so that server get it */
        send(sockfd, name, sizeof(name), 0);
    }

    return 0;
}
