#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd[2];
    char c;
    pipe(fd);

    if(fork()) // родитель
    {
        close(fd[0]);
        c = 0;
        while(write(fd[1], &c, 1) > 0)
        {
            c++;
        }
    }
    else  // дочерний процесс
    {
        dup2(fd[0], 0); // подменили stdin
        close(fd[0]);
        close(fd[1]);
        execl("prog", "prog", NULL); // запустили новую программу для которой
        // stdin = pipe
    }
}
