/**
 * @file libarbys.cpp
 *
 * @brief Basically a standar library for the Van Turco microkernel
 */
#ifdef __DEBUG
#include<stdio.h>
#include<cstdlib>
using namespace std;
#define panic(val, ...) printf(val ,##__VA_ARGS__)
#else
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#endif
/*int strcmp(char* comparated, char* comparator){
    int diferences = 0;
    for(int i = 0;true;i++){
        if (comparated[i] == '\0' || comparator[i] == '\0'){
            return diferences;
        }
        if (comparated[i] != comparator[i]){
            diferences++;
        }
    }
}*/

template <typename T>
struct promise_L
{
    T value;
    bool is_done = false;
};

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

class string_L : public vector_L<char>
{
public:
    string_L new_from(char *array, int size, int allocated = 0)
    {
        this->value = array;
        this->size = size;
        this->allocated = allocated;
        return *this;
    }

    string_L print()
    {
        for (int i = 0; i < this->size; i++)
        {
            printf("%c", this->value[i]);
        }
        printf("\n");
        return *this;
    }

    string_L empty()
    {
        this->value[0] = '\0';
        this->size = 0;
        return *this;
    }

    string_L copy()
    {
        char *copy = allocate_D(this->allocated);
        for (int i = 0; i < this->size; i++)
        {
            copy[i] = this->value[i];
        }
        return string_L::new_from(copy, this->size, this->allocated);
    }

    string_L &push(char value_new) override
    {
        if (this->size + 2 <= this->allocated)
        {
            printf("Found space %d/%d\n",size,allocated);

            this->value[size] = value_new;
            this->value[size + 1] = '\0';
            this->size++;
            return *this;
        }
            printf("NOT Found space %d/%d (New: %d)\n",size,allocated,allocated*2);

        char *new_T = allocate_D(this->allocated * 2);
        for (int i = 0; i < this->size; i++)
        {
            new_T[i] = this->value[i];
        }

        new_T[size] = value_new;
        new_T[size + 1] = '\0';
        this->size += 1;
        this->allocated *= 2;
        delete[] this->value;
        this->value = new_T;
        return *this;
    }
};

#ifndef __DEBUG

promise_L<char> read_into(string_L& buffer)
{
    promise_L<char> f;
    f.is_done = false;


    int c = getchar_timeout_us(0);
    if (c != PICO_ERROR_TIMEOUT)
    {
        printf("character: %c, size:%d\n",c,buffer.size);
        if ((char)c == '\n')
        {
            buffer.push('\n');
            printf("GETTING COMMAND\n");
            buffer.print();
            printf("\n");
            //process_command(buffer);
            f.is_done = true;
            f.value = (char)c;
            return f;
        }
        else
        {
            buffer.push((char)c);
        }
    }
    return f;
}
#endif


int process_command(string_L buffer){
    vector_L<string_L> arguments;
    string_L internal_buffer; 
    internal_buffer.allocate(32);
    printf("==== New Command ====\n");
    for (int i = 0; i < buffer.size; i++){
        if ((buffer[i] == ' ' || buffer[i] == '\n') && !internal_buffer.is_empty() ){
            printf("Found space %d\n",i);
            printf("Size: %d allocated: %d\n",internal_buffer.size,internal_buffer.allocated);
            internal_buffer.print();
            string_L temp = internal_buffer.copy();
            printf("Temp Size: %d allocated: %d\n",temp.size,temp.allocated);
            arguments.push(temp);
            printf("pushed");
            internal_buffer.empty();
        }
        else{
        printf("Found char %c at %d\n",buffer[i],i);
            internal_buffer.push(buffer[i]);
        }
    }

    if (!internal_buffer.is_empty()){

printf("Pushing final argument\n");
        arguments.push(internal_buffer);
    }
    else{
        printf("clearing\n");
    internal_buffer.clear();
    }
printf("counting %d\n",arguments.size);
    for (int i = 0; i < arguments.size; i++){
        arguments[i].print();
    }

    printf("Clearing arguments\n");
    arguments.clear();
    printf("==== Command End ====\n");
    return 0;
}