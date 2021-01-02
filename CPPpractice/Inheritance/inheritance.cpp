#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class A
{
public:
    A(int age) { _age = age; }

    int GetAge() { return _age; }

private:
    int _age;
};


class B : public A
{
public:
    B(int age, const char* name) : A(age)
    {
        _name = strdup(name);
    }

    char* GetName() { return _name;  }

    ~B() { delete _name; }

private:
    char* _name;
};


class C : public B
{
public:
    C(int age, const char* name, const char* surname) : B(age, name)
    {
        _surname = strdup(surname);
    }

    char* GetSurname() { return _surname; }

    ~C() { delete _surname; }

private:
    char* _surname;
};


int main()
{
    B b(19, "Dmitry");
    printf("%s: %d\n", b.GetName(), b.GetAge());

    C c(20, "Dima", "Karpovich");
    printf("%s %s: %d\n", c.GetName(), c.GetSurname(), c.GetAge());

    return 0;
}