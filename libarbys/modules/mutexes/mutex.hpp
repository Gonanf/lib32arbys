#include <libarbys.hpp>
#ifndef LIBARBYS_MUTEXES
#define LIBARBYS_MUTEXES

class mutex{
    private:
    unsigned int* data;
    bool wait_list;

    public:

    void lock(){
        this->wait_list = 0;
        return;
    };

    void unlock(){
        this->wait_list = 0;
        return;
    };

    #ifdef KERNEL32_SYSCALL
    mutex* get(/*Later add a timeout here*/){
        asm volatile("svc #0");
        return this;
    }
    #endif

};

#endif