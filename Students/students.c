#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    FILE* file;
    file = fopen("text.txt", "r");

    struct Node* list = CreateList();

    AddStudents(file, list);
    PrintStudents(list);

    return 0;
}
