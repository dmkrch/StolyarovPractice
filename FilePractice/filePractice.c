#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char* charPtr = (char*)malloc(sizeof(char)*10);

    int fileDescriptor = open("input.txt", O_RDONLY);

    int count = read(fileDescriptor, charPtr, 10);

    printf("readed:%d\n%s\n", count, charPtr);

    return 0;
}
