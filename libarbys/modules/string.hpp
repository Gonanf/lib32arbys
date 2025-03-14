
#ifndef LIBARBYS_STRING
#define LIBARBYS_STRING
#include "../libarbys.hpp"

class string_L : public vector_L<char>
{
public:
    static string_L new_from(char *array, int size)
    {
        string_L new_l;
        new_l.value = array;
        new_l.size = size;
        new_l.allocated = size+1;

        return new_l;
    }

    string_L print()
    {
        for (int i = 0; i < this->size; i++)
        {
            //printf("%c", this->value[i]);
        }
        //printf("\n");
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
        return string_L::new_from(copy, this->size);
    }

    string_L &push(char value_new) override
    {
        if (this->size + 2 <= this->allocated)
        {
            //printf("Found space %d/%d\n", size, allocated);

            this->value[size] = value_new;
            this->value[size + 1] = '\0';
            this->size++;
            return *this;
        }
        //printf("NOT Found space %d/%d (New: %d)\n", size, allocated, allocated * 2);

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


    promise_L<char> read_character()
    {
        promise_L<char> f;
        f.is_done = false;

        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT)
        {
            if ((char)c == '\n')
            {
                this->push('\n');
                this->print();
                // process_command(buffer);
                f.is_done = true;
                f.value = (char)c;
                return f;
            }
            else
            {
                this->push((char)c);
            }
        }
        return f;
    }
    vector_L<string_L> split()
    {
        vector_L<string_L> arguments;
        string_L internal_buffer;
        //internal_buffer.allocate(32);
        for (int i = 0; i < this->size; i++)
        {
            if ((this->value[i] == ' ' || this->value[i] == '\n') && !internal_buffer.is_empty())
            {
                arguments.push(internal_buffer.copy());
                internal_buffer.empty();
            }
            else
            {
                internal_buffer.push(this->value[i]);
            }
        }

        if (!internal_buffer.is_empty())
        {

            arguments.push(internal_buffer);
        }
        else
        {
            internal_buffer.clear();
        }
        for (int i = 0; i < arguments.size; i++)
        {
            arguments[i].print();
        }

        return arguments;
    }
};
#endif