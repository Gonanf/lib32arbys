#ifndef LIBARBYS
#define LIBARBYS
#ifdef __DEBUG
#include<stdio.h>
#include<cstdlib>
using namespace std;
#define panic(val, ...) printf(val ,##__VA_ARGS__)
#define getchar_timeout_us(val) getchar()
#define PICO_ERROR_TIMEOUT -1
#else
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#endif

#include "./libarbys.cpp"
#include "./modules/sorts.hpp"
#include "./modules/promise.hpp"
#include "./modules/vector.hpp"
#include "./modules/string.hpp"

#endif