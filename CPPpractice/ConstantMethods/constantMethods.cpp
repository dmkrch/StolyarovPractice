#include <math.h>
#include <stdio.h>
#include <string.h>

class Human
{
    private:
        int age;
        char* name;
    public:
        Human(int age, const char* name)
        {
            this->age = age;
            this->name = strdup(name);
        }

        char* GetName() const { return name; }
        int GetAge() const { return age; }
};

void ModifyHuman(const Human* hm)
{
    printf("name: %s\nage: %d\n", hm->GetName(), hm->GetAge());
}

int main()
{
    Human hm1(19, "Dima");
    
    /* here we pass address of Human, so we actually path Human* hm, but in function we use
       it like pointer that points to constant section of memory, so we can't modify the
       instance that we've passed. What is more, we neither can modify the values nor
       use ordinary methods. We can only use methods with 'const' type, so that compiler
       is sure that we can't modify instance in these methods, but only read-use */
    ModifyHuman(&hm1);


    /* here we show that we are still able to use const methods of our class */
    printf("name: %s\nage: %d\n", hm1.GetName(), hm1.GetAge());

    /* output:
        name: Dima,
        age: 19
        name:Dima,
        age: 19 
    */
   
    return 0;
}
