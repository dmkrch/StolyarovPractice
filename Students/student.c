#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"


struct Student* CreateStudent(char* name, int group, int mark)
{
    struct Student* student = (struct Student*)malloc(sizeof(struct Student));

    student->name = strdup(name);
    student->group = group;
    student->mark = mark;

    return student;
}
