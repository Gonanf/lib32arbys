#include "./kernel.hpp"

void sleep(unsigned int time)
{
    asm volatile(
        "mov r0, #1 \n\t"
        "ldr r1, %[tm] \n\t"
        "svc #0 \n\t"
        : 
        : [tm] "m" (time)
        : "r0", "r1", "memory");
    return;
}

void yield()
{
    asm volatile(
        "mov r0, #0 \n\t"
        "svc #0 \n\t"
        :
        :
        : "r0", "memory");
    return;
}

void exit(int code)
{
    asm volatile(
        "mov r0, #2 \n\t"
        "ldr r1, %[cd] \n\t"
        "svc #0\n\t"
        :
        : [cd] "m" (code)
        : "r0","r1","memory");
    return;
}

unsigned short send(unsigned short pid_to, int type, int data)
{
    asm volatile(
        "mov r0, #3 \n\t"
        "mov r1, %0 \n\t"
        "mov r2, %1 \n\t"
        "mov r3, %2 \n\t"
        "svc #0 \n\t"
        :
        : "r" (pid_to), "r" (type), "r" (data)
        : "r0","r1","r2","r3","memory"
        );

    return 0;
}

unsigned short poll(struct message *&reciver)
{
    struct message *msg_dir;
    asm volatile("mov r0, #4");
    asm volatile("svc #0");
    asm volatile("mov %0, r0" : "=r"(msg_dir));

    if (msg_dir->type != -1)
    {
        reciver = msg_dir;
        return 0;
    }
    return -1;
}

struct message *recive()
{
    struct message *msg_dir;

    while (true)
    {
        asm volatile("mov r0, #4");
        asm volatile("svc #0");

        asm volatile("mov %0, r0" : "=r"(msg_dir));

        if (msg_dir->type != -1)
        {
            break;
        }
    }
    return msg_dir;
}

struct process_info get_process_info()
{
    struct process_info process;
    asm volatile("mov r0, #5");
    asm volatile("svc #0");
    asm volatile("mov %0, r0" : "=r"(process.PID));
    return process;
}
