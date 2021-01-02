#include <stdio.h>
#include "fileException.h"

unsigned int line_count_in_file(const char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if (!file)
        throw FileException(fileName,
            "couldn't open for line counting");

    return 5;
}
int main()
{
    int lines = 0;
    try
    {
        lines = line_count_in_file("/home/dmkrch/cProgs/CPPpractice/ExceptionHandling/fileException.cpp");
        printf("%d\n", lines);
    }
    catch(FileException ex)
    {
        printf("%s, code: %d\n", ex.GetName(), ex.GetErrno());
    }
    return 0;
}