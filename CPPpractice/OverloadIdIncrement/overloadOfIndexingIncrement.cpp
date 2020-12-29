#include <stdio.h>


class IntVar
{
private:
    int var;
public:
    IntVar() { var = 0; }
    int GetValue() { return var; }
    const IntVar& operator++() { ++var; return *this; }
    const IntVar& operator++(int) { ++var; return *this; }
    const IntVar& operator--() { --var; return *this; }
    const IntVar& operator--(int) { -- var; return *this; }
    void operator= (int value) { var = value; }
    operator int() const {}
};


class IntVarArray
{
private:
    IntVar* arr;
    unsigned int size;

public:
    IntVarArray() { size = 16; arr = new IntVar[16]; }
    IntVar& operator[](unsigned int idx);
    unsigned int Size() { return size; }

private:
    void Resize(unsigned int idx);
};


IntVar& IntVarArray::operator[](unsigned int idx)
{
    if (idx >= size)
        Resize(idx);
    return arr[idx];
}

void IntVarArray::Resize(unsigned int required_index)
{
    unsigned int new_size = size;

    while(new_size <= required_index)
        new_size *= 2;

    /* allocating memory to new array */
    IntVar* new_array = new IntVar[new_size];

    /* copying previous data */
    for (unsigned int i = 0; i < size; i++)
        new_array[i] = arr[i];

    delete [] arr;

    arr = new_array;
    size = new_size;    
}


int main()
{
    IntVarArray arr;

    for (unsigned int i = 1; i <= 15; ++i)
    {
        arr[i] = i % 5;
    }

    for (unsigned int i = 1; i <= 30; ++i)
    {
        arr[i]++;
        printf("%d, ", arr[i]);
        arr[i]--;

        if(i % 5 == 0)
            printf("\n");
    }
}