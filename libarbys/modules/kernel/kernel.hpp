#ifndef LIBARBYS_KERNEL
#define LIBARBYS_KERNEL

struct message{
    unsigned int type;
    unsigned int data;
    unsigned int from;
};

struct process_info{
    unsigned int PID;
    unsigned int core_number;
    unsigned int priority;
};

void sleep(unsigned int time);
void yield();
void exit(unsigned int code);
//unsigned short send(unsigned short pid_to, int type, int data);
//unsigned short poll(struct message *&reciver); //Recive message without waiting
//struct message* recive(); //Recive message blocking
//struct process_info get_process_info();
//struct process_info posix_spawn();
//struct process_info signal_exit();




#include"./kernel.cpp"

#endif