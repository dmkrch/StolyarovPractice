#include <stdio.h>

template <class T>
class Array
{
private:
    T* p;
    T init;
    unsigned int size;
public:
    Array(T in) : p(0), init(in), size(0) {}
    ~Array() { if(p) delete[] p; }
    T& operator[](unsigned int idx)
    {
        if (idx >= size) Resize(idx);
        return p[idx];
    }
    int Size() const { return size; }
    void Show()
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            printf("%d ", p[i]);
        }
    }
private:
    void Resize(unsigned int required_index)
    {
        unsigned int new_size = size==0 ? 8 : size;
        while(new_size <= required_index)
            new_size *= 2;
        T* new_array = new T[new_size];

        for (unsigned int i = 0; i < new_size; ++i)
            new_array[i] = i < size ? p[i] : init;

        if(p) delete[] p;
        p = new_array;
        size = new_size;
    }

    void operator=(const Array<T>& ref) {}
    Array(const Array<T>& ref) {}
};



int main()
{
    Array<int> arr1(0);

    for (int i = 0; i < 5; ++i)
    {
        arr1[i*2] = 100;
    }

    arr1.Show();

    return 0;
}