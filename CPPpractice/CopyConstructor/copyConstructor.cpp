#include <math.h>
#include <stdio.h>
#include <string.h>


class Human
{
    private:
        char* name;
        int age;
    public:
        /* default constructor */
        Human()  { name = new char[20]; }

        /* copy constructor */
        Human(const Human& hm)
        {
            name = new char[20];
            age = hm.age;

            for (int i = 0; i < 20; ++i)
            {
                name[i] = hm.name[i];
            }
        }

        char* GetName() { return name; }
        void SetName(const char* name) { this->name = strdup(name); }

        ~Human() { delete [] name; }
};

void f(Human hm)
{
    printf("Hello, ");
}


int main()
{
    Human h1;

    h1.SetName("Dmitriy");

    printf("%s\n", h1.GetName());
  
    /* here we pass object to function. So the function will call copy
       constructor when creating copy of object that we've passed. It's
       like: Human hm2(hm1) */
    f(h1);

    /* if we didn't have the copy constructor, here we would have an
       error, because if we pass object by value, function creates a
       copy of passed object, but it just copies everything. So 
       after function, this variable calls destructor, that deletes 
       allocated memory for the same memory area */
    printf("%s\n", h1.GetName());


    /* in all these examples we call copy constructor */
    Human h2(h1);
    Human h3 = h2;
    Human h4 = Human(h3);
    Human* pHuman = new Human(h4);

    printf("my name is %s\n", pHuman->GetName());


    return 0;
}
