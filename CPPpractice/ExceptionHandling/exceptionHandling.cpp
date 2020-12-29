#include <stdio.h>
#include "fileException.h"

int main()
{

    FileException fileEx1("test.txt", "comment number 1");

    printf("%s\n", fileEx1.GetComment());
    printf("%s\n", fileEx1.GetName());

    return 0;
}