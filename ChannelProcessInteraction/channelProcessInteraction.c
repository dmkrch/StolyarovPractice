#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd[2];
    int p1, p2;
    char* data = (char*)malloc(100*sizeof(char));

    pipe(fd);
    p1 = fork();

    if (p1 == 0) // child #1
    {
        char dataWrite[] = "hello\n";
        close(fd[0]);
        write(fd[1], dataWrite, 6);

        exit(0);
    }

    p2 = fork();

    if (p2 == 0) // child #2
    {
        close(fd[1]);

        read(fd[0], data, 6);

        exit(0);
    }


    /* parent */
    close(fd[0]);
    close(fd[1]);

    printf("%s",data);

}
