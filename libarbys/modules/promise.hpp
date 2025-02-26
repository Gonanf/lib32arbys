#include"../libarbys.hpp"
#ifndef LIBARBYS_PROMISE
#define LIBARBYS_PROMISE
template <typename T>
struct promise_L
{
    T value;
    bool is_done = false;
};
#endif