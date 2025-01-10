#ifndef LIBARBYS_PROCESS
#define LIBARBYS_PROCESS
enum{SLEEP,READY,RUNNING,INTERRUPTED};

typedef int func(void);
#include"../../libarbys/libarbys.hpp"

#include"./tests/test_functions.hpp"
#include"./process.cpp"

#endif