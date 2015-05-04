#ifndef AAA_MEM_H
#define AAA_MEM_H

#include "types.h"

volatile void put32(void* addr, u32 val);
volatile u32  get32(void* addr);

void mem_barrier();

#endif /* AAA_MEM_H */
