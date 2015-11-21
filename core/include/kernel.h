#ifndef ALEK_KERNEL_H
#define ALEK_KERNEL_H

#include <types.h>

extern "C" void panic(const char *reason = nullptr);
extern "C" void set_clock_hz(u16 hz);

#endif