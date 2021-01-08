#include <stdio.h>
#include <string.h>

template <class T>
bool sort_less(T a, T b)
{
    return a < b;
}

template <>
bool sort_less<const char*>(const char* a, const char* b)
{
    return strcmp(a, b) < 0;
}


// for first example
template <class T>
void sort(T* array, int len)
{
    for (int start = 0; ; start++)
    {
        bool done = true;
        for (int i = len - 2; i >= start; i--)
            if (sort_less<T>(array[i+1], array[i]))
            {
                T tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
                done = false;
            }
        if (done)
            break;
    }
}



// for second example
class Point
{
public: 
    Point()
    {
        x = y = z = 0;
    }

    Point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    int x;
    int y;
    int z;
};


template<class T1, class T2>
class MyClass
{
public:
    MyClass(T1 value, T2 value1)
    {
        this->value = value;
        this->value1 = value1;
    }

    void DataTypeSize()
    {
        printf("value: %lu\nvalue1: %lu\n", sizeof(value), sizeof(value1));
    }

    T1 Foo() { return value; }
    T2 Foo1() { return value1; }
private:
    T1 value;
    T2 value1;
};



int main()
{
    // example 1
    int arr[] = {2, 5, 2, 8, 21, 3, 7, -5};
    int arrLength = 8;

    sort<int>(arr, arrLength);

    for (int i = 0; i < arrLength; i++)
        printf("%d ", arr[i]);
    
    printf("\n");



    // example 2
    MyClass<double, int> c(5.7, 8);
    c.DataTypeSize();

    Point point(2,5,8);
    MyClass<Point, int> c1(point, 9);
    c1.DataTypeSize();

    int b = c.Foo();
    int d = c1.Foo1();
}