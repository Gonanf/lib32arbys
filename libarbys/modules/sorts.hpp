#ifndef LIBARBYS_SORTS
#define LIBARBYS_SORTS
#include"./vector.hpp"
#include "../libarbys.hpp"

template <typename T>
vector_L<T> quicksort(vector_L<T> vec, int from, int to, bool reverse)
{
    if (from >= to)
    {
        return vec;
    }
    T pivot = vec[to];
    int index = from;
    for (int i = from; i < to; i++)
    {
        if (reverse ? vec[i] >= pivot : vec[i] <= pivot)
        {
            swap(vec[i], vec[index]);
            index++;
        }
    }
    swap(vec[index],vec[to]);

    quicksort(vec,from,index-1,reverse);
    quicksort(vec,index+1,to,reverse);

    return vec;
}
#endif