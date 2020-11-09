#ifndef STUDENT_H_SENTRY
#define STUDENT_H_SENTRY


struct Student
{
    char* name;
    int group;
    int mark;
};

struct Student* CreateStudent(char* name, int group, int mark);


#endif
