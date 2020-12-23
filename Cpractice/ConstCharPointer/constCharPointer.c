#include <stdio.h>
#include <stdlib.h>

void Function(char* line)
{
    for (int i = 0; i < 5; ++i)
    {
        line[i] = 'a';
    }

    printf("%s\n", line);
}

int main()
{
    char line1[] = "Hello, world";      // array of char
    char* line2 = "Hello, world";       // pointer that points to literal in some space of memory
    const char* line3 = "Hello, world"; // pointer that points to literal in some constant space of memory
    char* line4 = (char*)malloc(10);    // pointer that has memory to store some data

    line4 = "Hello, world";

    Function(line1);
    //Function(line2);  // error
    //Function(line3);  // error
    Function(line4);

    return 0;
}
