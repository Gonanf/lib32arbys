#include"../libarbys.hpp"



//TODO: Add sorts, reallocation, pop and remove.
template <typename T>
class vector_L
{
protected:
    T *allocate_D(int size)
    {
        T *value = new T[size];
        if (!value)
        {
            panic("Out of memory for vector");
        }
        printf("Allocated %d objects\n", size);
        return value;
    }

public:
    T *value = nullptr;
    int size = 0;
    int allocated = 0;

    operator T *() const
    {
        return value;
    }

    vector_L()
    {
        this->allocated = 2;
        this->value = allocate_D(allocated);
    }

    bool is_empty()
    {
        return size == 0;
    }

    vector_L<T> copy()
    {
        T *copy = allocate_D(this->allocated);
        for (int i = 0; i < this->size; i++)
        {
            copy[i] = this->value[i];
        }
        return vector_L<T>{
            copy,
            this->size,
            this->allocated,
        };
    }

    static vector_L<T> new_allocate(int size_n)
    {
        return vector_L<T>{
            allocate_D(size_n),
            0,
            size_n,
        };
    }

    vector_L<T> allocate(int size_n)
    {
        this->value = allocate_D(size_n);
        this->allocated = size_n;
        return *this;
    }

    virtual vector_L<T> &push(T value_new)
    {
        if (this->size + 1 <= allocated)
        {
            printf("Found space %d/%d\n",size,allocated);
            this->value[size] = value_new;
            this->size++;
            return *this;
        }
        printf("Not Found space %d/%d (New: %d)\n",size,allocated,allocated*2);
        T *new_T = allocate_D(this->allocated * 2);
        for (int i = 0; i < this->size; i++)
        {
            new_T[i] = this->value[i];
        }
        new_T[size] = value_new;
        this->size += 1;
        this->allocated *= 2;
        delete[] this->value;
        this->value = new_T;
        return *this;
    }

    vector_L<T> clear()
    {
        delete[] this->value;
        this->size = 0;
        this->allocated = 2;
        this->value = allocate_D(2);
        return *this;
    }

    T &operator[](int index)
    {
        if (index >= this->size)
        {
            panic("Index out of bounds, (index: %d >= size: %d)\n", &index, &this->size);
        }
        return this->value[index];
    }
};