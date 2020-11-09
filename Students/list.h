#ifndef LIST_H_SENTRY
#define LIST_H_SENTRY


struct Node
{
    struct Node* nextPointer;
    struct Student* student;
};

struct Node* CreateList();

void AddStudent(struct Node* list, struct Student* student);

void PrintStudents(struct Node* list);

void AddStudents(FILE* file, struct Node* list);


#endif
