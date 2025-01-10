#ifdef __DEBUG
#include<stdio.h>
#include<cstdlib>
using namespace std;
#else
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#endif

#include "../libarbys.hpp"

int main(){
    string_L buffer;
    buffer.new_from((char*)"amongas",8);
    for (int i = 0; i < 10; i++)
    {
                process_command(buffer);
    }

    return 0;
}