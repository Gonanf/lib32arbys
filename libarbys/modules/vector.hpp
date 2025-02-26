#ifndef LIBARBYS_VECTORS
#define LIBARBYS_VECTORS
#include"../libarbys.hpp"
#include"./sorts.hpp"


template <typename T>
class vector_L
{
protected:
    T *allocate_D(int size)
    {
        T *value = new T[size];
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

    virtual bool operator>=(const vector_L& R) const{
        return this->size>=R.size;
    }

    virtual bool operator>(const vector_L& R) const{
        return this->size>R.size;
    }
    
    virtual bool operator<=(const vector_L& R) const{
        return this->size<=R.size;
    }

    virtual bool operator<(const vector_L& R) const{
        return this->size<R.size;
    }

    virtual bool operator==(const vector_L& R) const{
        return this->size==R.size;
    }

    virtual bool operator-(const int R) const{
        return this->size-R;
    }

     virtual bool operator+(const int R) const{
        return this->size+R;
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


    vector_L<T> pop(){
        this->size--;
        return *this;
    }

    vector_L<T> discard(unsigned int position){
        for (int i = position+1; i < this->size; i++){
            this->value[i-1] = this->value[i]; 
        }
        this->size--;
        return *this;
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

    static vector_L<T> new_allocate(unsigned int size_n)
    {
        return vector_L<T>{
            allocate_D(size_n),
            0,
            size_n,
        };
    }

    vector_L<T> allocate(unsigned int size_n)
    {
        this->value = allocate_D(size_n);
        this->allocated = size_n;
        return *this;
    }

    virtual vector_L<T> &push(T value_new)
    {
        if (this->size + 1 <= allocated)
        {
            this->value[size] = value_new;
            this->size++;
            return *this;
        }
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

    T &operator[](unsigned int index)
    {
        if (index >= this->size)
        {
            //panic("Index out of bounds, (index: %d >= size: %d)\n", &index, &this->size);
        }
        return this->value[index];
    }

    vector_L<T> sort(bool reverse = false){
        quicksort(*this,0,this->size-1,reverse);
        return *this;
    }

    vector_L<T> sort_copy(bool reverse = false){
        return quicksort(this->copy(),0,this->size-1,reverse);
    }
};
#endif