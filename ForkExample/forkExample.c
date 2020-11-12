#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int p = fork();
    if (p == 0)
    {
        printf("I'm the child\n");
    }
    else
    {
        printf("I'm the parent\n");
    }
}
