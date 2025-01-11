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
    string_L buffer = string_L::new_from((char*)"amongas es god",15);
    vector_L<string_L> args = buffer.split();
    for(int i = 0; i < args.size; i++){
        args[i].print();
    }
    printf("\n\n");
    args.sort();
    for(int i = 0; i < args.size; i++){
        args[i].print();
    }
    printf("\n\n");

    args.sort(true);
    for(int i = 0; i < args.size; i++){
        args[i].print();
    }
    printf("\n\n");


    return 0;
}