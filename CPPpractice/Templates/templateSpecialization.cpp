#include <stdio.h>


// example for template class specialization
template<class T>
class Printer
{
public:
    void Print(T value)
    {
        printf(value);
    }
};

template<>
class Printer<const char*>
{
public: 
    void Print(const char* message)
    {
        printf("___%s___", message);
    }
};



int main()
{
    Printer<const char*> stringPrinter;
    Printer<int> intPrinter;

    intPrinter.Print(5234);
    stringPrinter.Print("Hello world!");    // will print ___...___
    


    return 0;
}