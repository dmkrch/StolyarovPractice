#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;
    pid = fork();

    if (pid == -1)  // ошибка порождения процесса
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) // порожденный процесс (потомок)
    {
        execlp("ls", "ls", "-l", "-a", "/var", NULL);
        perror("ls"); // exec вернул управление - значит была ошибка
        exit(1); // завершаем процесс с кодом неуспеха
    }

    // родительский процесс
    wait(NULL); // дожидаемся завершения

    printf("Ok\n");
    return 0;
}
