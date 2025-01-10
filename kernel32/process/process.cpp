class process{
    public:
    int PID;
    char *name;
    int status;
    func* function;
    //process *children;
    //uint32_t regs[15];


static process create(func* function){
    process p;

    return p;
    /*process actual;
    __asm volatile(
        "mov %0, r0\n\t"
        "mov %1, r1\n\t"
        "mov %2, r2\n\t"
        "mov %3, r3\n\t"
        "mov %4, r4\n\t"
        "mov %5, r5\n\t"
        "mov %6, r6\n\t"
        "mov %7, r7\n\t"
        "mov %8, r8\n\t"
        "mov %9, r9\n\t"
        "mov %10, r10\n\t"
        "mov %11, r11\n\t"
        "mov %12, r12\n\t"
        "mov %13, r13\n\t" //PSP
        "mov %14, r14\n\t" //LR
        "mov %15, r15\n\t" //PC
        : "=r" (actual.regs[0]),
        "=r" (actual.regs[1]),
        "=r" (actual.regs[2]),
        "=r" (actual.regs[3]),
        "=r" (actual.regs[4]),
        "=r" (actual.regs[5]),
        "=r" (actual.regs[6]),
        "=r" (actual.regs[7]),
        "=r" (actual.regs[8]),
        "=r" (actual.regs[9]),
        "=r" (actual.regs[10]),
        "=r" (actual.regs[11]),
        "=r" (actual.regs[12]),
        "=r" (actual.regs[13]),
        "=r" (actual.regs[14]),
        "=r" (actual.regs[15]),
    );*/

    




}

};
