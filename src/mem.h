#ifndef MEM_H
#define MEM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

volatile void put32(void* addr, u32 val);
volatile u32  get32(void* addr);

void mem_barrier();

#ifdef __cplusplus
}
#endif
#endif