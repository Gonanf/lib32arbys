#include"../../libarbys/libarbys.hpp"

typedef struct process{
    int PID;
    char *name;
    process *children;
    uint32_t regs[12];
    uint32_t lr;
    uint32_t pc;
    uint32_t rpc;
};

process fork(){
    process actual;
    __asm volatile{
        "mov %0, r0\n\t"
        "mov %0, r1\n\t"
        "mov %0, r2\n\t"
        "mov %0, r3\n\t"
        "mov %0, r4\n\t"
        "mov %0, r5\n\t"
        "mov %0, r6\n\t"
        "mov %0, r7\n\t"
        "mov %0, r8\n\t"
        "mov %0, r9\n\t"
        "mov %0, r10\n\t"
        "mov %0, r11\n\t"
        "mov %0, r12\n\t"
        "mov %0, lr\n\t"
        "mov %0, pc\n\t"
        "mov %0, psr\n\t"
    }
}
