#include"../libarbys.hpp"

template <typename T>
struct promise_L
{
    T value;
    bool is_done = false;
};