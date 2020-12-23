#include <stdio.h>

#ifndef BUFFER_SIZE
#error Please specify the buffer buffer size
#endif


#if defined(USE_FIRST_VARIANT)
void PrintMsg()
{
    printf("first\n");
}
#elif defined(USE_SECOND_VARIANT)
void PrintMsg()
{
    printf("second\n");
}
#else
void PrintMsg()
{
    printf("else\n");
}
#endif





int main()
{
    PrintMsg();
    return 0;
}
