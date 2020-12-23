#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "student.h"

struct Node* CreateList()
{
    struct Node* list = (struct Node*)malloc(sizeof(struct Node));

    list->nextPointer = NULL;
    list->student = NULL;

    return list;
}

void AddStudent(struct Node* list, struct Student* student)
{
    if (list->nextPointer == NULL && list->student == NULL) // if head is null with information
    {
        list->student = student;
    }

    else
    {
        while(list->nextPointer != NULL)                    // after this this is the place we need to place our new Node
        {
            list = list->nextPointer;
        }

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

        newNode->nextPointer = NULL;
        newNode->student = student;

        list->nextPointer = newNode;
    }
}

void PrintStudents(struct Node* list)
{
    int i = 1;

    while(list->nextPointer != NULL)
    {
        printf("Student #%d\n%s%d\n%d\n\n", i, list->student->name, list->student->group, list->student->mark);
        list = list->nextPointer;

        ++i;
    }
    if (i > 1)
    {
        printf("Student #%d\n%s%d\n%d\n\n", i, list->student->name, list->student->group, list->student->mark);
    }
}

void AddStudents(FILE* file, struct Node* list)
{
    char name[20];
    char data[20];
    int group;
    int mark;

    while(fgets(name, 20, file) != NULL)
    {
        fgets(data, 20, file);
        group = atoi(data);
        fgets(data, 20, file);
        mark = atoi(data);

        struct Student* student = CreateStudent(name, group, mark);
        AddStudent(list, student);
    }
}
