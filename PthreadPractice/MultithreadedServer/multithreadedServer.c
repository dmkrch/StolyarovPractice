#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"


#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100
#define THREAD_POOL_SIZE 20

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t enqueue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t dequeue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void* thread_function(void* arg);
void* handle_connection(void* p_client_socket);
int check(int exp, const char* msg);



int main(int argc, char** argv)
{
    int server_socket;
    int client_socket;
    int addr_size;
 
    SA_IN server_addr;
    SA_IN client_addr;

    // first we create a bunch of threads to handle future connections
    for(int i = 0; i < THREAD_POOL_SIZE; ++i)
    {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }

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

        while(true)
        {
            printf("Waiting for connections...\n");
            //wait for, and eventually accept an incoming connection
            addr_size = sizeof(SA_IN);

            check(client_socket = 
                accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size),
                "Accept failed");
            
            printf("Connected!\n");

            
            int* pclient = (int*)malloc(sizeof(int));
            *pclient = client_socket;
             
            pthread_mutex_lock(&enqueue_mutex);
            enqueue(pclient);
            pthread_cond_signal(&condition_var);
            pthread_mutex_unlock(&enqueue_mutex);
        }

        return 0;
}


void* thread_function(void* arg)
{
    while(true)
    {
        int* pclient;

        pthread_mutex_lock(&dequeue_mutex);
        pthread_cond_wait(&condition_var, &dequeue_mutex);
        pclient = dequeue();
        pthread_mutex_unlock(&dequeue_mutex);

        if (pclient != NULL)
        {
            // we have a connection
            handle_connection(pclient);
        }
    }
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

void* handle_connection(void* p_client_socket)
{
    int client_socket = *((int*)p_client_socket);
    free(p_client_socket);      // we really dont need this anymore
    char buffer[BUFSIZE];
    size_t bytes_read;
    char actualpath[PATH_MAX+1];

    //read the clients's message -- the name of the file to read 
    bytes_read = recv(client_socket, buffer, BUFSIZE, 0);

    check(bytes_read, "recv error");
    //buffer[msgsize-1] = 0; // null terminate the message and remove \n
        
    printf("REQUEST: %s\n", buffer);
    fflush(stdout);
        
        
    // validity of file path
    if (realpath(buffer, actualpath) == NULL)
    {
        printf("ERROR(bad path): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    // open file
    FILE* fp = fopen(actualpath, "r");
    if (fp == NULL)
    {
        printf("ERROR(open): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    // read file contents and send them to client
    // note this is an example program and it is insecure
    // a real program would probably limit the client to certain files
    while((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0)
    {
        printf("sending %zu bytes\n", bytes_read);
        write(client_socket, buffer, bytes_read);
    }
    close(client_socket);
    fclose(fp);
    printf("closing connection\n");
    return NULL;
}